#pragma once

#include "CVector2.h"
#include "CPlayer.h"
#include "Defines.h"
#include <SDL.h>

class CBall
{
public:
	CBall();
	void Update(float timeStep, CPlayer& p1, CPlayer& p2);
	void Render(SDL_Renderer& renderer, SDL_Texture& ballImage) const; 
	const CVector2& GetPosition() const;
	void SetPosition(CVector2 newPosition);
	const CVector2& GetVelocity() const;
	void SetVelocity(CVector2 newVelocity);
	void AddVelocity(CVector2 addend);
	float GetMass() const;
	void SetMass(const float newMass);
private:
	float ballRadius;	
	float mMass;
	CVector2 mPosition;
	CVector2 mVelocity;
	SDL_Rect ballCanvas;
};

inline const CVector2& CBall::GetPosition() const
{
	return mPosition;
}

inline void CBall::SetPosition(CVector2 newPosition)
{
	mPosition = newPosition;
}

inline const CVector2& CBall::GetVelocity() const
{
	return mVelocity;
}

inline void CBall::SetVelocity(CVector2 newVelocity)
{
	mVelocity = newVelocity;
}

inline void CBall::AddVelocity(CVector2 addend)
{
	mVelocity = mVelocity + addend;
}

inline float CBall::GetMass() const
{
	return mMass;
}

inline void CBall::SetMass(float newMass)
{
	mMass = newMass;
}