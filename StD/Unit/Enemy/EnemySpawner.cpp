#include "EnemySpawner.h"
#include "EnemyManager.h"
#include "ECircle.h"


EnemySpawner::EnemySpawner(Vec2Float pos, const std::vector<EnemyType>& spawnList)
{
	pos_ = pos;
	spawnList_ = spawnList;
	enemyMng_ = &EnemyManager::Instance();
	cnt_ = 0.0f;
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::Spawn(EnemyType type)
{
	auto& enemy = enemyMng_->CreateEnemy(type);
	enemy.SetPosition(pos_);
}

void EnemySpawner::Update(float deltaTime)
{
	cnt_++;
	if (cnt_ > 60.0f && spawnList_.size() > 0)
	{
		cnt_ = 0.0f;
		Spawn(spawnList_.back());
		spawnList_.pop_back();
	}
}
