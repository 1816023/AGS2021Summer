#pragma once
#include "Trap.h"
class Support:
	public Trap
{
public:
	Support(Vec2Float _pos);
	~Support();

	void Draw() override;
	float Efficacy(float num, bool flag) override;
	int TrapCost(int cost) override;
};

