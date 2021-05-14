#pragma once
#include <DxLib.h>
#include "../VECTOR2.h"

class Trap
{
public:
	Trap() {};
	virtual ~Trap() {};
	virtual void Draw() {};

private:
	virtual int TrapCost(int cost) = 0;

protected:
	VECTOR2 pos;
	int cnt;
	int image;
};

