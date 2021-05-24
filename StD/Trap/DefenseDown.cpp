#include "DefenseDown.h"

DefenseDown::DefenseDown(Vec2Float _pos)
{
	image = LoadGraph(L"data/image/Defense_down.png");
	pos = _pos;
}

DefenseDown::~DefenseDown()
{
}

void DefenseDown::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, image, false);
}

float DefenseDown::Efficacy(float num, bool flag)
{
	if (flag)
	{
		num = num - (num / 3);
	}
	return num;
}

int DefenseDown::TrapCost(int cost)
{
	int _cost = 10;
	return cost - _cost;
}
