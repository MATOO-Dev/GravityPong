#pragma once

#include "Defines.h"
#include "CBall.h"
#include "CPlayer.h"
#include <SDL.h>
#include <iostream>

class GameManager
{
private:
	CPlayer& player1;
	CPlayer& player2;
	CBall& ball;
public:
	GameManager(CPlayer& player1Ref, CPlayer& player2Red, CBall& ballRef);
	void Update(EGameState& currentGameState);
	void WatchBall();
	void ResetBoard();
	void ServeBall();
	void ToggleGameState(EGameState& currentGameState);
	void DisplayScore(CPlayer& targetPlayer, SDL_Renderer& renderer, int xCoord);
};