#include "EnemySpawner.h"
#include "EnemyManager.h"
#include "ECircle.h"


EnemySpawner::EnemySpawner(Vec2Float pos, const std::vector<EnemyType>& spawnList, EnemyManager& enemyMng)
{
	pos_ = pos;
	spawnList_ = spawnList;
	enemyMng_ = &enemyMng;
}

EnemySpawner::~EnemySpawner()
{
	delete(enemyMng_);
}

void EnemySpawner::Spawn(EnemyType type)
{
	auto& enemy = enemyMng_->CreateEnemy(type);
	enemy.SetPosition(pos_);
}
