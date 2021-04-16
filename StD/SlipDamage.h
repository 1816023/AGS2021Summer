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
private:
	VECTOR2 pos;
};

