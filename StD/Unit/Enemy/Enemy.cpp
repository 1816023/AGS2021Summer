#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(MapInfo& mapInfo)
{
	// x方向にスケーリング
	scale_ = E_SIZE_X / mapInfo.chipSize.x;
	state_.isDead = false;
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

unsigned int Enemy::GetHP()
{
	return state_.life;
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
	return state_.isDead;
}
