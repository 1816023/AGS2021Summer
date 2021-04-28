#pragma once
#include "TrapManager.h"
class SlipDamage :
	public TrapManager
{
public:
	SlipDamage(VECTOR2 _pos);
	~SlipDamage();

	void Draw() override;
	int Damage(int hp, bool flag);
};

