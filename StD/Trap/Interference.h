#pragma once
#include "TrapManager.h"
class Interference :
	public TrapManager
{
public:
	Interference(VECTOR2 _pos);
	~Interference();

	void Draw() override;
	float Delay(float speed, bool flag);
};

