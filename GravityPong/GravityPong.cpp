// GravityPong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Defines.h"
#include "CPlayer.h"
#include "CBall.h"
#include "GameManager.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#define TICK_INTERVAL 5

int main(int argc, char* argv[])
{	
	//creates objects
	CPlayer* Player1 = new CPlayer('w', 's', 'a', 'd', SDL_SCANCODE_SPACE, CVector2(windowWidth / 4, windowHeight / 2), 0);
	CPlayer* Player2 = new CPlayer('i', 'k', 'j', 'l', SDL_SCANCODE_RSHIFT, CVector2(windowWidth / 4 * 3, windowHeight / 2), 1);
	CBall* myBall = new CBall();
	GameManager* GMInstance = new GameManager(*Player1, *Player2, *myBall);
	EGameState activeGameState = EGameState::Active;

	//starts sdl
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		//creates window and renderer
		SDL_Window* Window = NULL;
		SDL_Renderer* Renderer = NULL;

		//create a window using sdl
		if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &Window, &Renderer) == 0)
		{
			SDL_bool running = SDL_TRUE;

			//loads textures
			SDL_Texture* gravityImage = IMG_LoadTexture(Renderer, "data/textures/gravity.bmp");
			SDL_SetTextureAlphaMod(gravityImage, 40);
			SDL_Texture* ballImage = IMG_LoadTexture(Renderer, "data/textures/ball.bmp");
			SDL_Texture* gameOverImage = IMG_LoadTexture(Renderer, "data/textures/GameOverText.bmp");
			SDL_Rect gameOverCanvas = { 450, 250, 1000, 500 };
			SDL_Texture* pausedImage = IMG_LoadTexture(Renderer, "data/textures/PausedText.bmp");
			SDL_Rect pausedCanvas = { 450, 250, 1000, 500 };

			//serves ball
			GMInstance->ServeBall();

			//game loop
			while (running)
			{
				int before = SDL_GetTicks();
				SDL_Event event;

				//manages background and foreground color
				SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(Renderer);
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);


				//manages current Game State
				switch (activeGameState)
				{
				case(EGameState::Active):
					//updates movement
					Player1->Update((float)TICK_INTERVAL / 1000.f);
					Player2->Update((float)TICK_INTERVAL / 1000.f);
					myBall->Update((float)TICK_INTERVAL / 1000.f, *Player1, *Player2);
					//renders
					Player1->Render(*Renderer, *gravityImage);
					Player2->Render(*Renderer, *gravityImage);
					myBall->Render(*Renderer, *ballImage);
					//manages functions centrally
					GMInstance->WatchBall();
					GMInstance->Update(activeGameState);
					GMInstance->DisplayScore(*Player1, *Renderer, 50);
					GMInstance->DisplayScore(*Player2, *Renderer, 1835);
					break;
				case(EGameState::Paused):
					//renders the game, but doesn't update movement
					Player1->Render(*Renderer, *gravityImage);
					Player2->Render(*Renderer, *gravityImage);
					myBall->Render(*Renderer, *ballImage);
					//this is required in order to get back from paused to active
					GMInstance->Update(activeGameState);
					//displays score
					GMInstance->DisplayScore(*Player1, *Renderer, 50);
					GMInstance->DisplayScore(*Player2, *Renderer, 1835);
					//shows pause text
					SDL_RenderCopy(Renderer, pausedImage, NULL, &pausedCanvas);
					break;
				case(EGameState::GameOver):
					//displays score
					GMInstance->DisplayScore(*Player1, *Renderer, 50);
					GMInstance->DisplayScore(*Player2, *Renderer, 1835); 
					//shows game over text
					SDL_RenderCopy(Renderer, gameOverImage, NULL, &gameOverCanvas);
					break;
				}

				//exits program
				if (GMInstance->Exit(activeGameState, running))
				{
					running = SDL_FALSE;
				}

				//displays the rendered image
				SDL_RenderPresent(Renderer);

				{
					int after = SDL_GetTicks();
					int ticks = after - before;
					if (ticks < 60)
					{
						SDL_Delay(60 - ticks);
					}
					ticks = SDL_GetTicks() - before;
				}

				{
					//exits the Game loop upon the event SDL_QUIT occuring
					while (SDL_PollEvent(&event)) {
						if (event.type == SDL_QUIT) {
							running = SDL_FALSE;
						}
					}
				}
			}
		}
		if (Renderer)
			SDL_DestroyRenderer(Renderer);
		if (Window)
			SDL_DestroyWindow(Window);
	}
	SDL_Quit();
	return 0;
}