#include "EnemySpawner.h"
#include "EnemyManager.h"
#include "Mob/ECircle.h"
#include "../../Map/Map.h"

EnemySpawner::EnemySpawner(Vec2Float pos, EnemyManager& enemyMng)
{
	for (int i = 0; i < 10; i++)
	{
		spawnList_.emplace_back(EnemyType::Circle);
	}
	for (int i = 0; i < 9; i++)
	{
		root_.emplace_back(RootDir::LEFT);
	}
	/*for (int i = 0; i < 6; i++)
	{
		root_.emplace_back(RootDir::DOWN);
	}
	for (int i = 0; i < 9; i++)
	{
		root_.emplace_back(RootDir::RIGHT);
	}
	for (int i = 0; i < 9; i++)
	{
		root_.emplace_back(RootDir::UP);
	}
	for (int i = 0; i < 9; i++)
	{
		root_.emplace_back(RootDir::LEFT);
	}
	for (int i = 0; i < 3; i++)
	{
		root_.emplace_back(RootDir::DOWN);
	}*/
	pos_ = pos;
	enemyMng_ = &enemyMng;
	cnt_ = 0.0f;
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::Spawn(EnemyType type)
{
	auto& enemy = enemyMng_->CreateEnemy(type);
	enemy.SetPosition(pos_);
	enemy.SetRoot(root_);
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

int EnemySpawner::GetRemainSpawnCnt()
{
	return spawnList_.size();
}
