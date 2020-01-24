#include "GameManager.h"

GameManager::GameManager(CPlayer& player1Ref, CPlayer& player2Ref, CBall& ballRef):
player1(player1Ref),
player2(player2Ref),
ball(ballRef)
{}

void GameManager::watchBall()
{
	if (ball.GetPosition().GetX() < 0 || ball.GetPosition().GetX() > windowWidth)
	{
		resetBoard();
		serveBall();
	}
}

void GameManager::resetBoard()
{
	ball.SetVelocity(CVector2(0, 0));
	ball.SetPosition(CVector2(windowWidth / 2, windowHeight / 2));
	player1.SetVelocity(CVector2(0, 0));
	player1.SetPosition(CVector2(windowWidth / 4, windowHeight / 2));
	player2.SetVelocity(CVector2(0, 0));
	player2.SetPosition(CVector2(windowWidth / 4 * 3, windowHeight / 2));
}

void GameManager::serveBall()
{
	CVector2 newBallDirection = (windowWidth / 2, windowHeight / 2);
	float newBallHeading = rand() % 365;
	newBallDirection.rotate(newBallHeading);
	//subject to change
	float ballSpeed = 500;
	//
	ball.SetVelocity(newBallDirection.normalize() * ballSpeed);
}

void GameManager::ToggleGameState(EGameState currentGameState)
{
	if (currentGameState == EGameState::Active)
		currentGameState = EGameState::Paused;
	else
		currentGameState = EGameState::Active;
}