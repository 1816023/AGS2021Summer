#pragma once
#include "Trap.h"
class SlipDamage :
	public Trap
{
public:
	SlipDamage(Vec2Float _pos);
	~SlipDamage();

	void Draw() override;
	float Efficacy(float num, bool flag) override;
	int TrapCost(int cost) override;
};

