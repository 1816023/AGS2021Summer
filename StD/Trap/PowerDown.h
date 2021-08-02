#pragma once
#include "Trap.h"
class PowerDown :
    public Trap
{
public:
	PowerDown(Vec2Float _pos);
	~PowerDown();

	void Draw() override;
	float Update(float num) override;
	int TrapCost(int cost) override;
};

