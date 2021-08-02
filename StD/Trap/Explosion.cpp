#include "Explosion.h"

Explosion::Explosion(Vec2Float _pos)
{
	image = LoadGraph(L"data/image/explosion.png");
	pos = _pos;
	cnt = 0;
}

Explosion::~Explosion()
{
}

void Explosion::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, image, false);
}

float Explosion::Update(float num)
{
	cnt++;
	if (cnt >= 60)
	{
		num -= 20;
		cnt = 0;
	}

	return num;
}

int Explosion::TrapCost(int cost)
{
	int _cost = 10;
	return cost - _cost;
}
