#include "EnemyManager.h"
#include "ECircle.h"
#include "../../Map/Map.h"
#include <algorithm>

using namespace std;

EnemyManager::EnemyManager(Map& map)
{
	MapInfo mapInfo;
	mapInfo.chipSize = map.GetChipSize();
	mapInfo.mapSize = map.GetMapSize();
	prototype_.emplace(EnemyType::Circle, new ECircle(mapInfo));
}

EnemyManager::~EnemyManager()
{
}
Enemy& EnemyManager::CreateEnemy(EnemyType type)
{
	auto enemy = prototype_[type]->CreateClone();
	enemies_.emplace_back(enemy);
	return *enemies_.back();
}

void EnemyManager::Update(float deltaTime)
{
	for (auto& enemy : enemies_)
	{
		enemy->Update(deltaTime);
	}
	enemies_.erase(remove_if(enemies_.begin(), enemies_.end(),
		[](shared_ptr<Enemy>& enemy)
		{
			return enemy->IsDeath();
		}), enemies_.end());
}

void EnemyManager::Draw()
{
	for (auto& enemy : enemies_)
	{
		enemy->Draw();
	}
}

EnemyList& EnemyManager::GetEnemies()
{
	return enemies_;
}
