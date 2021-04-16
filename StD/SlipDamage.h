#pragma once
#include "TrapManager.h"
class SlipDamage :
	public TrapManager
{
public:
	SlipDamage();
	~SlipDamage();

	void Update() override;
private:
	void Draw() override;
};

