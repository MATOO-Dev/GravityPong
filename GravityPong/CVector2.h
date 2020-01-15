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
	void rotate(float angleDeg);
	float length();
	CVector2 normalize();
	float GetY() const;
	float GetX() const;
	void SetX(float newX);
	void SetY(float newY);
	~CVector2();
private:
	float x;
	float y;
};

inline CVector2 operator+ (const CVector2& first, const CVector2& second)
{
	return CVector2(first.GetX() + second.GetX(), first.GetY() + second.GetY());
}

inline CVector2 operator*(const CVector2& base, const float& multiplier)
{
	return(CVector2(base.GetX() * multiplier, base.GetY() * multiplier));
}

inline float CVector2::length()
{
	return(sqrt((x * x) + (y * y)));
}

inline CVector2 CVector2::normalize()
{
	return(CVector2(x / this->length(), y / this->length()));
}

inline float CVector2::GetX() const
{
	return x;
}

inline float CVector2::GetY() const
{
	return y;
}

inline void CVector2::SetX(float newX)
{
	x = newX;
}

inline void CVector2::SetY(float newY)
{
	y = newY;
}
