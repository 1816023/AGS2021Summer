#pragma once
#include "Trap.h"
class Interference :
	public Trap
{
public:
	Interference(VECTOR2 _pos);
	~Interference();

	void Draw() override;
	float Delay(float speed, bool flag);
	int TrapCost(int cost) override;
};

