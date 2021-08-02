#include "Interference.h"

Interference::Interference(Vec2Float _pos)
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

float Interference::Update(float num)
{
	return num * 0.3;
}

int Interference::TrapCost(int cost)
{
	int _cost = 10;
	return cost - _cost;
}
