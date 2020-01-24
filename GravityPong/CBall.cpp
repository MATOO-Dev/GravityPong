#include "CBall.h"
#include <iostream>

#define G (6.674 * (10^1))	//gravitational constant, in reality 6.674 * (10^-11)

CBall::CBall() :
	mPosition(windowWidth / 2, windowHeight / 2),
	mVelocity(0, 0),
	ballRadius(5),
	mMass(1),
	ballCanvas({ 0, 0, (int)ballRadius * 2, (int)ballRadius * 2 })
{}

void CBall::Update(float timeStep, CPlayer& player1, CPlayer& player2)
{
	if (mPosition.GetDistance(player1.GetPosition()) < player1.GetGravityRadius() && player1.GetGravityState())
	{
		//calculates gravitational force based on Newtons gravitational law
		float F = G * ((player1.GetMass() * GetMass()) / (mPosition.GetDistance(player1.GetPosition()) * mPosition.GetDistance(player1.GetPosition())));
		float gravityMultiplier = 20;
		CVector2 directionVector = player1.GetPosition() - GetPosition();
		directionVector = directionVector.normalize();
		F = F * gravityMultiplier;
		directionVector = directionVector * F;
		mVelocity = mVelocity + directionVector;
	}
	if (mPosition.GetDistance(player2.GetPosition()) < player2.GetGravityRadius() && player2.GetGravityState())
	{
		//calculates gravitational force based on Newtons gravitational law
		float F = G * ((player2.GetMass() * GetMass()) / (mPosition.GetDistance(player2.GetPosition()) * mPosition.GetDistance(player2.GetPosition())));
		float gravityMultiplier = 20;
		CVector2 directionVector = player2.GetPosition() - GetPosition();
		directionVector = directionVector.normalize();
		F = F * gravityMultiplier;
		directionVector = directionVector * F;
		mVelocity = mVelocity + directionVector;
	}
	if (mPosition.GetDistance(player1.GetPosition()) < player1.GetGraphicsRadius() || mPosition.GetDistance(player2.GetPosition()) < player2.GetGraphicsRadius())
	{
		if (mPosition.GetDistance(player1.GetPosition()) < mPosition.GetDistance(player2.GetPosition()))
			player2.IncrementScore();
		else
			player1.IncrementScore();

		SetVelocity(CVector2(0, 0));
		SetPosition(CVector2(windowWidth / 2, -100));
	}

	SetPosition(GetPosition() + (GetVelocity() * timeStep));

	if (mPosition.GetX() < 0)
	{
		player2.IncrementScore();
	}
	if (mPosition.GetX() > windowWidth)
	{
		player1.IncrementScore();
	}
	if (mPosition.GetY() < 0)
	{
		SetVelocity(CVector2(mVelocity.GetX(), mVelocity.GetY() * -1));
	}
	if (mPosition.GetY() > windowHeight)
	{
		SetVelocity(CVector2(mVelocity.GetX(), mVelocity.GetY() * -1));
	}

	ballCanvas.x = mPosition.GetX() - (ballCanvas.w / 2);
	ballCanvas.y = mPosition.GetY() - (ballCanvas.h / 2);
}

void CBall::Render(SDL_Renderer& renderer, SDL_Texture& ballImage) const
{
	SDL_RenderCopy(&renderer, &ballImage, NULL, &ballCanvas);
}