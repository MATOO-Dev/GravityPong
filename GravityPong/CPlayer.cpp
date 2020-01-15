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
	graphicsRadius(10),
	rotationRate(20)
{
	for (int i = 0; i < 8; i++)
	{
		graphicsOffsets.push_back(CVector2(mPosition.GetX() - graphicsRadius, mPosition.GetY()));
		graphicsOffsets[i].rotate(45 * i);
		std::cout << graphicsOffsets[i].GetX() << ", " << graphicsOffsets[i].GetY() << std::endl;
		graphicsOffsets[i].SetX(mPosition.GetX() + graphicsOffsets[i].GetX());
		graphicsOffsets[i].SetY(mPosition.GetY() + graphicsOffsets[i].GetY());
	}
}

void CPlayer::Update(float timeStep)
{
	SetPosition(GetPosition() + (GetVelocity() * timeStep));
	SetVelocity(GetVelocity() * dragMultiplier);

	const Uint8* keyInput = SDL_GetKeyboardState(NULL);
	
	

	if (keyInput[SDL_GetScancodeFromKey(upKey)])
	{
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
	for (int i = 0; i < graphicsOffsets.size(); i++)
	{
		graphicsOffsets[i].rotate(rotationRate);
	}
}

void CPlayer::Render(SDL_Renderer& renderer) const
{
	std::vector<CVector2> rotatedOffsets;
	for (int i = 0; i < graphicsOffsets.size(); i++)
	{
		rotatedOffsets.push_back(graphicsOffsets[i]);
	}
	for (int i = 0; i < rotatedOffsets.size(); i++)
	{
		CVector2 lineOrigin = mPosition + rotatedOffsets[i];
		CVector2 lineTarget;

		if (i < rotatedOffsets.size() - 4)
			lineTarget = mPosition + rotatedOffsets[i + 4];

		else
			lineTarget = mPosition + rotatedOffsets[0 + i];

		SDL_RenderDrawLine(&renderer, (int)lineOrigin.GetX(), (int)lineOrigin.GetY(), (int)lineTarget.GetX(), (int)lineTarget.GetY());
	}
}