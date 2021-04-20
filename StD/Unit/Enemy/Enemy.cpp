#include "Enemy.h"

Enemy::Enemy()
{
}
Enemy::~Enemy()
{
}
void Enemy::Update(float deltaTime)
{
}

void Enemy::Draw()
{
}

void Enemy::SetPosition(Vec2Float pos)
{
	state_.pos = pos;
}

bool Enemy::IsDeath()
{
	return isDeath_;
}
