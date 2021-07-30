#pragma once
#include "Trap.h"
class Explosion :
	public Trap
{
public:
	Explosion(Vec2Float _pos);
	~Explosion();

	void Draw() override;
	float Update(float num) override;
	int TrapCost(int cost) override;
};

