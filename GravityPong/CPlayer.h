#pragma once
#include "CVector2.h"
#include "Defines.h"
#include <SDL.h>
#include <vector>

class CPlayer
{
public:
	CPlayer(char up, char down, char left, char right, SDL_Scancode grav, CVector2 startPosition, int side);
	~CPlayer();
	void Update(float timeStep);
	void Render(SDL_Renderer& renderer, SDL_Texture& gravityImage) const;
	const CVector2& GetPosition() const;
	void SetPosition(CVector2 newPosition);
	const CVector2& GetVelocity() const;
	void SetVelocity(CVector2 newVelocity);
	void AddVelocity(CVector2 addend);
	float GetMass() const;
	void SetMass(const float newMass);
	void IncrementScore();
	float GetGravityRadius();
	float GetGraphicsRadius();
	bool GetGravityState();
	int GetScore();
private:
	const char upKey;
	const char downKey;
	const char rightKey;
	const char leftKey;
	const SDL_Scancode gravKey;
	CVector2 mPosition;
	CVector2 mVelocity;
	const float moveSpeed = 500;
	const float dragMultiplier = 0.75;
	float mScore;
	float mMass;
	float gravityRadius;
	float graphicsRadius;
	float rotationRate;
	bool mGravityActive;
	int boardSide;
	SDL_Rect gravityCanvas;
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
	//subject to review
	mVelocity = mVelocity + addend;
}

inline float CPlayer::GetMass() const
{
	return mMass;
}

inline void CPlayer::SetMass(float newMass)
{
	mMass = newMass;
}

inline float CPlayer::GetGravityRadius()
{
	return gravityRadius;
}

inline bool CPlayer::GetGravityState()
{
	return mGravityActive;
}

inline float CPlayer::GetGraphicsRadius()
{
	return graphicsRadius;
}

inline void CPlayer::IncrementScore()
{
	mScore++;
}

inline int CPlayer::GetScore()
{
	return mScore;
}