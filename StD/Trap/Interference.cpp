#include "Interference.h"

Interference::Interference(VECTOR2 _pos)
{
	image = LoadGraph(L"data/image/interference.png");
	pos = _pos;
	cnt = 0;
}

Interference::~Interference()
{
}

void Interference::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, image, false);
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

int Interference::TrapCost(int cost)
{
	int _cost = 10;
	return cost - _cost;
}
