#include "Support.h"

Support::Support(VECTOR2 _pos)
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

int Support::Healing(int hp, bool flag)
{
	if (flag)
	{
		cnt++;
		if (cnt >= 60)
		{
			hp++;
			cnt = 0;
		}
	}

	return hp;
}

int Support::TrapCost(int cost)
{
	int _cost = 10;
	return cost - _cost;
}
