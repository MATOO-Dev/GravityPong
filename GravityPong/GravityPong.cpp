// GravityPong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Defines.h"
#include "CPlayer.h"
#include "CBall.h"
#include <iostream>
#include <SDL.h>

#define TICK_INTERVAL 5

int main(int argc, char* argv[])
{
	CPlayer* Player1 = new CPlayer(0, 0, 'w', 's', 'a', 'd', (450, 500));
	CPlayer* Player2 = new CPlayer(0, 0, 'i', 'k', 'j', 'l', (650, 500));
	CBall* myBall = new CBall(0, 0); 
	EGameState activeGameState = EGameState::Active;
	static ETheme activeTheme = ETheme::Dark;

	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		SDL_Window* Window = NULL;
		SDL_Renderer* Renderer = NULL;

		//create a window using sdl
		if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &Window, &Renderer) == 0)
		{
			SDL_bool completed = SDL_FALSE;

			//game loop
			while (!completed)
			{
				int before = SDL_GetTicks();
				SDL_Event event;

				//manages background and foreground color in regards to active theme
				switch (activeTheme)
				{
				case(ETheme::Light):
					SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
					SDL_RenderClear(Renderer);
					SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					break;
				case(ETheme::Dark):
					SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					SDL_RenderClear(Renderer);
					SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
					break;
				}


				//manages current Game State
				switch (activeGameState)
				{
				case(EGameState::Menu):
					break;
				case(EGameState::Active):
					Player1->Update((float)TICK_INTERVAL / 1000.f);
					Player2->Update((float)TICK_INTERVAL / 1000.f);
					Player1->Render(*Renderer);
					Player2->Render(*Renderer);
					break;
				case(EGameState::Paused):
					break;
				case(EGameState::Settings):
					break;
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
					std::cout << ticks << "\n";
				}

				{
					//exits the Game loop upon the event SDL_QUIT occuring
					while (SDL_PollEvent(&event)) {
						if (event.type == SDL_QUIT) {
							completed = SDL_TRUE;
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