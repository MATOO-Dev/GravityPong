#pragma once
#include "CVector2.h"
#include "Defines.h"
#include <SDL.h>
#include <vector>

class CPlayer
{
public:
	CPlayer(float xVal, float yVal, char up, char down, char left, char right, CVector2 startPosition);
	~CPlayer();
	void Update(float timeStep);
	void Render(SDL_Renderer& renderer) const;
	const CVector2& GetPosition() const;
	void SetPosition(CVector2 newPosition);
	const CVector2& GetVelocity() const;
	void SetVelocity(CVector2 newVelocity);
	void AddVelocity(CVector2 addend);
private:
	float x;
	float y;
	const char upKey;
	const char downKey;
	const char rightKey;
	const char leftKey;
	CVector2 mPosition;
	CVector2 mVelocity;
	const float moveSpeed = 500;
	const float dragMultiplier = 0.75;
	float mScore;
	float eventHorizonRadius;
	float gravityRadius;
	float graphicsRadius;
	float rotationRate;
	CVector2 graphicsOffsets2[8];
	std::vector<CVector2> graphicsOffsets;
};

inline const CVector2& CPlayer::GetPosition() const
{
	return mPosition;
}

inline void CPlayer::SetPosition(CVector2 newPosition)
{
	mPosition = newPosition;
}

inline const CVector2& CPlayer::GetVelocity() const
{
	return mVelocity;
}

inline void CPlayer::SetVelocity(CVector2 newVelocity)
{
	mVelocity = newVelocity;
}

inline void CPlayer::AddVelocity(CVector2 addend)
{
	mVelocity = mVelocity + addend;
}