#include "PowerDown.h"

PowerDown::PowerDown(Vec2Float _pos)
{
	image = LoadGraph(L"data/image/power_down.png");
	pos = _pos;
}

PowerDown::~PowerDown()
{
}

void PowerDown::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, image, false);
}

float PowerDown::Efficacy(float num, bool flag)
{
	if (flag)
	{
		num = num - (num / 3);
	}
	return num;
}

int PowerDown::TrapCost(int cost)
{
	int _cost = 10;
	return cost - _cost;
}
