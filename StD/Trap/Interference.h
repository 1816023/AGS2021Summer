#pragma once
#include "Trap.h"
class Interference :
	public Trap
{
public:
	Interference(Vec2Float _pos);
	~Interference();

	void Draw() override;
	float Update(float num) override;
	int TrapCost(int cost) override;
};

