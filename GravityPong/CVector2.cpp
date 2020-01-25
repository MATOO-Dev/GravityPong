#include "Cvector2.h"

//default vector constructor
CVector2::CVector2() :
	x(0),
	y(0)
{}

//creates a Vector using 2 floats
CVector2::CVector2(float xVal, float yVal) :
	x(xVal),
	y(yVal)
{}

//creates a Vector between 2 points
CVector2::CVector2(CVector2 target, CVector2 origin) :
	x(target.x - origin.x),
	y(target.y - origin.y)
{}

//constructs a vector from an angle
CVector2::CVector2(float angleDeg) :
	x(cos(angleDeg* (pi / 180))),
	y(sin(angleDeg* (pi / 180)))
{}

//rotates a vector
void CVector2::Rotate(float angleDeg)
{
	float angleRad = angleDeg * (pi / 180);
	float x2 = cos(angleRad) * x - sin(angleRad) * y;
	float y2 = sin(angleRad) * x + cos(angleRad) * y;
	x = x2;
	y = y2;
}