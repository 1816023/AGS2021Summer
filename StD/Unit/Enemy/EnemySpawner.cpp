#include "EnemySpawner.h"
#include "EnemyManager.h"
#include "Mob/ECircle.h"
#include "../../Map/Map.h"
#include <cassert>
#include <algorithm>

EnemySpawner::EnemySpawner(Vec2Float pos, EnemyManager& enemyMng, Map& map, int spawnerId)
{
	/*for (int i = 0; i < 10; i++)
	{
		spawnEList_.emplace_back(EnemyType::Circle);
	}*/
	wave_ = 1;
	spawnEDatas_ = map.GetEnemyDatas()[wave_][spawnerId];
	std::sort(spawnEDatas_.begin(), spawnEDatas_.end(),
		[](EnemyData& lData, EnemyData& rData)
		{
			return lData.spawnTime > rData.spawnTime;
		});
	if (map.GetRoot().size() == 0)
	{
		assert(false);
	}
	root_ = map.GetRoot();
	/*for (int i = 0; i < 9; i++)
	{
		root_.emplace_back(RootDir::LEFT);
	}*/
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

void EnemySpawner::Spawn(EnemyData data)
{
	auto& enemy = enemyMng_->CreateEnemy(data.type);
	enemy.SetPosition(pos_);
	enemy.SetRoot(root_[data.rootID]);
}

void EnemySpawner::Update(float deltaTime)
{
	// “G‚ª‘¶Ý‚µ‚È‚¢ê‡
	if (spawnEDatas_.size() == 0)
	{
		return;
	}
	cnt_+= deltaTime;
	if (cnt_ > spawnEDatas_.back().spawnTime  && spawnEDatas_.size() > 0)
	{
		cnt_ = 0.0f;
		Spawn(spawnEDatas_.back());
		spawnEDatas_.pop_back();
	}
}

int EnemySpawner::GetRemainSpawnCnt()
{
	return static_cast<int>(spawnEDatas_.size());
}
