#pragma once
#include "Trap.h"
class Support:
	public Trap
{
public:
	Support(Vec2Float _pos);
	~Support();

	void Draw() override;
	float Update(float num) override;
	int TrapCost(int cost) override;
};

