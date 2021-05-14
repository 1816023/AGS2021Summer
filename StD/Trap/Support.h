#pragma once
#include "Trap.h"
class Support:
	public Trap
{
public:
	Support(VECTOR2 _pos);
	~Support();

	void Draw() override;
	int Healing(int hp, bool flag);
	int TrapCost(int cost) override;
};

