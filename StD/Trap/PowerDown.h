#pragma once
#include "Trap.h"
class PowerDown :
    public Trap
{
public:
	PowerDown(Vec2Float _pos);
	~PowerDown();

	void Draw() override;
	float Efficacy(float num, bool flag) override;
	int TrapCost(int cost) override;
};

