#include "Support.h"

Support::Support(VECTOR2 _pos)
{
	pos = _pos;
	cnt = 0;
}

Support::~Support()
{
}

void Support::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, image[TRAP_ID::SUPPORT], false);
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
