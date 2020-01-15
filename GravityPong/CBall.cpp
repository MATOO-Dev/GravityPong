#include "CBall.h"

#define G (6.674 * (10^100))	//gravitational constant, in reality 6.674 * (10^-11)

CBall::CBall() :
	mPosition(windowWidth / 2, windowHeight / 2),
	mVelocity(0, 0),
	ballRadius(5),
	mMass(10),
	ballCanvas({ 0, 0, (int)ballRadius * 2, (int)ballRadius * 2})
{}

void CBall::Update(float timeStep, CPlayer& player1, CPlayer& player2)
{
	if (mPosition.GetDistance(player1.GetPosition()) < gravityRadius)	
	{
		//calculates gravitational force based on Newtons gravitational law
		float F = G * ((player1.GetMass() * GetMass()) / (mPosition.GetDistance(player1.GetPosition()) * mPosition.GetDistance(player1.GetPosition())));

		//possibly: applies gravitational force similarly to lorentz force (?)
		//current: applies gravitational force directly

		mVelocity = mVelocity + (mPosition.GetDistance(player1.GetPosition()) * F) * -1;
	}

	SetPosition(GetPosition() + (GetVelocity() * timeStep));

	if (mPosition.GetX() < 0)
	{
		player2.Score();
		SetVelocity(CVector2(0, mVelocity.GetY()));
	}
	if (mPosition.GetX() > windowWidth)
	{
		player1.Score();
		SetVelocity(CVector2(0, mVelocity.GetY()));
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