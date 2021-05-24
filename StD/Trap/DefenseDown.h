#pragma once
#include "Trap.h"
class DefenseDown :
    public Trap
{
public:
	DefenseDown(Vec2Float _pos);
	~DefenseDown();

	void Draw() override;
	float Efficacy(float num, bool flag) override;
	int TrapCost(int cost) override;
};

