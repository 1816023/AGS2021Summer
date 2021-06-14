#include "EnemyManager.h"
#include "ECircle.h"
#include "../../Map/Map.h"
#include <algorithm>
#include "../../Object/Shot/ShotMng.h"

using namespace std;

EnemyManager::EnemyManager(Map& map)
{
	MapInfo mapInfo;
	mapInfo.chipSize = map.GetChipSize();
	mapInfo.mapSize = map.GetMapSize();
	prototype_.emplace(EnemyType::Circle, new ECircle(mapInfo));
	shotMng_ = std::make_unique<ShotMng>();
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
		shotMng_->AddBullet(enemy,enemy->GetPos());
		shotMng_->BulletMove(enemy, Vec2Float(100, 100));
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
	//shotMng_->Draw();
}

EnemyList& EnemyManager::GetEnemies()
{
	return enemies_;
}
