#pragma once

#include <math.h>

#define pi 3.14159265358

class CVector2
{
public:
	CVector2();
	CVector2(float xVal, float yVal);
	CVector2(CVector2 target, CVector2 origin);
	CVector2(float angleDeg);
	void Rotate(float angleDeg);
	float Length() const;
	CVector2 Normalize() const;
	float GetDistance(const CVector2 other) const;
	float GetY() const;
	float GetX() const;
	void SetX(float newX);
	void SetY(float newY);
private:
	float x;
	float y;
};

//adds 2 vectors
inline CVector2 operator+ (const CVector2& first, const CVector2& second)
{
	return CVector2(first.GetX() + second.GetX(), first.GetY() + second.GetY());
}

//subtracts 2 vectors
inline CVector2 operator- (const CVector2& first, const CVector2& second)
{
	return CVector2(first.GetX() - second.GetX(), first.GetY() - second.GetY());
}

//multiplies a vector by a float
inline CVector2 operator*(const CVector2& base, const float& multiplier)
{
	return(CVector2(base.GetX() * multiplier, base.GetY() * multiplier));
}

//returns the length of a vector
inline float CVector2::Length() const
{
	return(sqrt((x * x) + (y * y)));
}

//returns a normalized version of that vector
inline CVector2 CVector2::Normalize() const
{
	return(CVector2(x / this->Length(), y / this->Length()));
}

//calculates the distance between this and another vector
inline float CVector2::GetDistance(const CVector2 other) const
{
	CVector2 connection = CVector2(other - CVector2(x, y));
	return connection.Length();
}

//returns x
inline float CVector2::GetX() const
{
	return x;
}

//returns y
inline float CVector2::GetY() const
{
	return y;
}

//sets x
inline void CVector2::SetX(const float newX)
{
	x = newX;
}

//sets y
inline void CVector2::SetY(const float newY)
{
	y = newY;
}