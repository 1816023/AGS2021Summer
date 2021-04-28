#pragma once
#include "TrapManager.h"
class Explosion :
	public TrapManager
{
public:
	Explosion(VECTOR2 _pos);
	~Explosion();

	void Draw() override;
	int Damage(int hp, bool flag);
};

