#include "Interference.h"

Interference::Interference(VECTOR2 _pos)
{
	pos = _pos;
	cnt = 0;
}

Interference::~Interference()
{
}

void Interference::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, image[TRAP_ID::INTERFERENCE], false);
}

float Interference::Delay(float speed, bool flag)
{
	if (flag)
	{
		return speed * 0.3;
	}
	else
	{
		return speed;
	}
}
