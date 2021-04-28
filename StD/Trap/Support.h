#pragma once
#include "TrapManager.h"
class Support:
	public TrapManager
{
public:
	Support(VECTOR2 _pos);
	~Support();

	void Draw() override;
	int Healing(int hp, bool flag);
};

