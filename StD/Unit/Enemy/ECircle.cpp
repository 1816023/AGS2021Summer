#include "ECircle.h"

ECircle::ECircle() : Enemy()
{
}

ECircle::~ECircle()
{
}

void ECircle::Update(float deltaTime)
{
}

void ECircle::Draw()
{
	DrawCircle(state_.pos.x, state_.pos.y, 5, 0xfffffff);
}

void ECircle::SetPosition(Vec2Float pos)
{
}
