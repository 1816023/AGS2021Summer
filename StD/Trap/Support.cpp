#include "Support.h"

Support::Support(Vec2Float _pos)
{
	image = LoadGraph(L"data/image/support.png");
	pos = _pos;
	cnt = 0;
}

Support::~Support()
{
}

void Support::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, image, false);
}

float Support::Update(float num)
{
	
	cnt++;
	if (cnt >= 60)
	{
		num++;
		cnt = 0;
	}
	

	return num;
}

int Support::TrapCost(int cost)
{
	int _cost = 10;
	return cost - _cost;
}
