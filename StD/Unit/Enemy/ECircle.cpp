#include "ECircle.h"

ECircle::ECircle(Vec2Float pos) : Enemy(pos)
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
