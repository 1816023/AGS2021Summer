#pragma once
#include "Trap.h"
class Explosion :
	public Trap
{
public:
	Explosion(Vec2Float _pos);
	~Explosion();

	void Draw() override;
	float Efficacy(float num, bool flag) override;
	int TrapCost(int cost) override;
};

