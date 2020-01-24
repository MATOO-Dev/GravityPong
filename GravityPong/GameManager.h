#pragma once

#include "Defines.h"
#include "CBall.h"
#include "CPlayer.h"
#include <SDL.h>

class GameManager
{
private:
	CPlayer& player1;
	CPlayer& player2;
	CBall& ball;
public:
	GameManager(CPlayer& player1Ref, CPlayer& player2Red, CBall& ballRef);
	void watchBall();
	void resetBoard();
	void serveBall(); 
	static void ToggleGameState(EGameState currentGameState);
};

