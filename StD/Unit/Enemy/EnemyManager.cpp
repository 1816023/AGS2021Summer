#include "EnemyManager.h"
#include "ECircle.h"

EnemyManager::EnemyManager()
{
	prototype_.emplace(EnemyType::Circle, new ECircle());
}

Enemy& EnemyManager::CreateEnemy(EnemyType type)
{
	auto enemy = prototype_[type];
	enemies_.emplace_back(enemy);
	return *enemies_.back();
}

void EnemyManager::Update(float deltaTime)
{
	for (auto& enemy : enemies_)
	{
		enemy->Update(deltaTime);
	}
}

void EnemyManager::Draw()
{
	for (auto& enemy : enemies_)
	{
		enemy->Draw();
	}
}
