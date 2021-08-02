#pragma once
#include <DxLib.h>
#include "../VECTOR2.h"

class Trap
{
public:
	Trap() {};
	virtual ~Trap() {};
	virtual void Draw() = 0;
	virtual float Update(float num) = 0;
	virtual int TrapCost(int cost) = 0;

protected:
	Vec2Float pos;
	int cnt;
	int image;
};

