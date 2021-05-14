#pragma once
#include "Trap.h"
class SlipDamage :
	public Trap
{
public:
	SlipDamage(VECTOR2 _pos);
	~SlipDamage();

	void Draw() override;
	int Damage(int hp, bool flag);
	int TrapCost(int cost) override;
};

