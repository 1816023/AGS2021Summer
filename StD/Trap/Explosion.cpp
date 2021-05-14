#include "Explosion.h"

Explosion::Explosion(VECTOR2 _pos)
{
	image - LoadGraph(L"data/image/explosion.png");
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

int Explosion::Damage(int hp, bool flag)
{
	if (flag)
	{
		cnt++;
		if (cnt >= 60)
		{
			hp -= 20;
			cnt = 0;
		}
	}

	return hp;
}

int Explosion::TrapCost(int cost)
{
	int _cost = 10;
	return cost - _cost;
}
