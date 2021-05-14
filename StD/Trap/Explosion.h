#pragma once
#include "Trap.h"
class Explosion :
	public Trap
{
public:
	Explosion(VECTOR2 _pos);
	~Explosion();

	void Draw() override;
	int Damage(int hp, bool flag);
	int TrapCost(int cost) override;
};

