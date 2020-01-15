#include "CPlayer.h"
#include <iostream>

CPlayer::CPlayer(float xVal, float yVal, char up, char down, char left, char right, CVector2 startPosition) :
	x(xVal),
	y(yVal),
	upKey(up),
	downKey(down),
	leftKey(left),
	rightKey(right),
	mPosition(startPosition),
	mVelocity(0, 0),
	eventHorizonRadius(0),
	gravityRadius(0),
	graphicsRadius(5)
{
	for (int i = 0; i < graphicsOffsets.size(); i++)
	{
		graphicsOffsets[i] = CVector2(mPosition.GetX() - graphicsRadius, mPosition.GetY());
		graphicsOffsets[i].rotate(45 * i);
		std::cout << graphicsOffsets[i].GetX() << ", " << graphicsOffsets[i].GetY() << std::endl;
		graphicsOffsets[i].SetX(mPosition.GetX() + graphicsOffsets[i].GetX());
		graphicsOffsets[i].SetX(mPosition.GetY() + graphicsOffsets[i].GetY());
	}
}

void CPlayer::Update(float timeStep)
{
	SetPosition(GetPosition() + (GetVelocity() * timeStep));
	SetVelocity(GetVelocity() * dragMultiplier);

	const Uint8* keyInput = SDL_GetKeyboardState(NULL);
	
	

	if (keyInput[SDL_GetScancodeFromKey(upKey)])
	{
		std::cout << "down\n";
		AddVelocity(CVector2(0, -moveSpeed));
	}
	if (keyInput[SDL_GetScancodeFromKey(downKey)])
	{
		AddVelocity(CVector2(0, moveSpeed));
	}
	if (keyInput[SDL_GetScancodeFromKey(leftKey)])
	{
		AddVelocity(CVector2(-moveSpeed, 0));
	}
	if (keyInput[SDL_GetScancodeFromKey(rightKey)])
	{
		AddVelocity(CVector2(moveSpeed, 0));
	}

	//keeps Player in bounds(window)
	if (mPosition.GetX() < 0)
	{
		mPosition.SetX(0);
		SetVelocity(CVector2(0, mVelocity.GetY()));
	}
	if (mPosition.GetX() > windowWidth)
	{
		mPosition.SetX(windowWidth);
		SetVelocity(CVector2(0, mVelocity.GetY()));
	}
	if (mPosition.GetY() < 0)
	{
		mPosition.SetY(0);
		SetVelocity(CVector2(mVelocity.GetX() , 0));
	}
	if (mPosition.GetY() > windowHeight)
	{
		mPosition.SetY(windowHeight);
		SetVelocity(CVector2(mVelocity.GetX(), 0));
	}
}

void CPlayer::Render(SDL_Renderer& renderer) const
{
	for (int i = 0; i < graphicsOffsets.size(); i++)
	{
		graphicsOffsets[i].SetX(mPosition.GetX() + graphicsOffsets[i].GetX());
		graphicsOffsets[i].SetX(mPosition.GetY() + graphicsOffsets[i].GetY());
	}

	SDL_RenderDrawLine(&renderer, mPosition.GetX() - 25, mPosition.GetY(), mPosition.GetX() + 25, mPosition.GetY());
	SDL_RenderDrawLine(&renderer, graphicsOffsets[2].GetX(), graphicsOffsets[2].GetY(), graphicsOffsets[6].GetX(), graphicsOffsets[6].GetY());
}