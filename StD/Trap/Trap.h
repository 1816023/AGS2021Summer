#pragma once
#include <DxLib.h>
#include "../VECTOR2.h"

class Trap
{
public:
	Trap() {};
	virtual ~Trap() {};
	virtual void Draw() {};
	virtual float Efficacy(float num, bool flag) = 0;
	virtual int TrapCost(int cost) = 0;

protected:
	Vec2Float pos;
	int cnt;
	int image;
};

