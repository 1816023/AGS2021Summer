#include "SlipDamage.h"
#include "../MouseController.h"

SlipDamage::SlipDamage(Vec2Float _pos)
{
	image = LoadGraph(L"data/image/slip_damege.png");
	pos = _pos;
	cnt = 0;
}

SlipDamage::~SlipDamage()
{
}

void SlipDamage::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, image, false);
}

float SlipDamage::Efficacy(float num, bool flag)
{
	if (flag)
	{
		cnt++;
		if (cnt >= 60)
		{
			num--;
			cnt = 0;
		}
	}

	return num;
}

int SlipDamage::TrapCost(int cost)
{
	int _cost = 10;
	return cost - _cost;
}
