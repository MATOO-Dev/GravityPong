#include "GameManager.h"

GameManager::GameManager(CPlayer& player1Ref, CPlayer& player2Ref, CBall& ballRef) :
	player1(player1Ref),
	player2(player2Ref),
	ball(ballRef)
{}

GameManager::~GameManager()
{
	//delete *player1;
	//delete *player2;
	//delete ball;
}

//checks whether escape is pressed and ends game if score of 5 is reached
void GameManager::Update(EGameState& currentGameState)
{
	const Uint8* keyInput = SDL_GetKeyboardState(NULL);

	if (keyInput[SDL_Scancode(SDL_SCANCODE_ESCAPE)])
	{
		ToggleGameState(currentGameState);
	}

	if (player1.GetScore() == 5 || player2.GetScore() == 5)
	{
		player1.SetPosition(CVector2(windowWidth / 2, windowHeight / 2));
		player1.SetPosition(CVector2(windowWidth / 2, windowHeight / 2));
		currentGameState = EGameState::GameOver;
	}
}

//exits the game if enter is pressed while paused or ended
bool GameManager::Exit(EGameState& currentGameState, bool gameLoopRequirement)
{
	const Uint8* keyInput = SDL_GetKeyboardState(NULL);

	if (keyInput[SDL_Scancode(SDL_SCANCODE_RETURN)] && (currentGameState == EGameState::Paused || currentGameState == EGameState::GameOver))
	{
		return true;
	}
	else
		return false;
}

//checks ball position and calls resetboard and serveball if necessary
void GameManager::WatchBall()
{
	if (ball.GetPosition().GetX() < 0 || ball.GetPosition().GetX() > windowWidth)
	{
		ResetBoard();
		ServeBall();
	}
	if (ball.GetPosition().GetY() < -90)
	{
		ResetBoard();
		ServeBall();
	}
}

//resets player and ball positions and velocities
void GameManager::ResetBoard()
{
	ball.SetVelocity(CVector2(0, 0));
	ball.SetPosition(CVector2(windowWidth / 2, windowHeight / 2));
	player1.SetVelocity(CVector2(0, 0));
	player1.SetPosition(CVector2(windowWidth / 4, windowHeight / 2));
	player2.SetVelocity(CVector2(0, 0));
	player2.SetPosition(CVector2(windowWidth / 4 * 3, windowHeight / 2));
}

//shoots ball into a random direction
void GameManager::ServeBall()
{
	CVector2 newBallDirection = (windowWidth / 2, windowHeight / 2);
	int newBallHeading = rand() % 360;
	newBallDirection.Rotate(newBallHeading);
	//subject to change
	float ballSpeed = 500;
	//
	ball.SetVelocity(newBallDirection.Normalize() * ballSpeed);
}

//toggles between active and paused
void GameManager::ToggleGameState(EGameState& currentGameState)
{
	SDL_Delay(200);
	if (currentGameState == EGameState::Active)
		currentGameState = EGameState::Paused;
	else
		currentGameState = EGameState::Active;
}

//displays score
void GameManager::DisplayScore(CPlayer& targetPlayer, SDL_Renderer& renderer, int xCoord)
{
	int baseX = xCoord;
	int baseY = 50;

	//targetplayer.getscore() cannot be called in a switch, using multiple if functions instead
	if (targetPlayer.GetScore() > 0 && targetPlayer.GetScore() < 5)
	{
		for (int i = 0; i < targetPlayer.GetScore(); i++)
		{
			SDL_RenderDrawLine(&renderer, baseX + (i * 5), baseY, baseX + (i * 5), baseY + 20);
		}
	}
	if (targetPlayer.GetScore() == 5)
	{
		for (int i = 0; i < targetPlayer.GetScore() - 1; i++)
		{
			SDL_RenderDrawLine(&renderer, baseX + (i * 5), baseY, baseX + (i * 5), baseY + 20);
		}
		SDL_RenderDrawLine(&renderer, baseX - 5, baseY + (20 / 2), baseX + (targetPlayer.GetScore() - 1) * 5, baseY + (20 / 2));
	}
}