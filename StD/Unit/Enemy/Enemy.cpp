#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(Map& map)
{
	map_ = &map;
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

void Enemy::SetRoot(std::vector<RootDir>& root)
{
	root_ = root;
}

bool Enemy::IsDeath()
{
	return isDeath_;
}
