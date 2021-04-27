#include "SlipDamage.h"
#include "MouseController.h"

SlipDamage::SlipDamage(VECTOR2 pos)
{
	this->pos = pos;
	cnt = 0;
}

SlipDamage::~SlipDamage()
{
}

void SlipDamage::Update()
{
}

void SlipDamage::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, slipDamage, false);
}

int SlipDamage::Damage(int hp, bool flag)
{
	if (flag)
	{
		cnt++;
		if (cnt >= 60)
		{
			hp--;
			cnt = 0;
		}
	}

	return hp;
}
