#include "SlipDamage.h"
#include "../MouseController.h"

SlipDamage::SlipDamage(VECTOR2 _pos)
{
	pos = _pos;
	cnt = 0;
}

SlipDamage::~SlipDamage()
{
}

void SlipDamage::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, image[TRAP_ID::SLIP_DAMAGE], false);
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
