#pragma once

#include "CVector2.h"
#include "Defines.h"

class CBall
{
public:
	CBall(float xVal, float yVal);
	void Update();
	void Render() const;
private:
	CVector2 mPosition;
};

