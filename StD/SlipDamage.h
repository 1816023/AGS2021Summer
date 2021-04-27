#pragma once
#include "TrapManager.h"
#include "VECTOR2.h"
class SlipDamage :
	public TrapManager
{
public:
	SlipDamage(VECTOR2 pos);
	~SlipDamage();

	void Update() override;
	void Draw() override;
	int Damage(int hp, bool flag);
private:
	VECTOR2 pos;
	int cnt;
};

