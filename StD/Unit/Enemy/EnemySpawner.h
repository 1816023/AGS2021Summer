#pragma once
#include "../../VECTOR2.h"
#include <vector>
#include "EnemyType.h"

// 敵を発生させるクラス
class EnemyManager;
class EnemySpawner
{
friend class EnemyManager;
public:
	EnemySpawner(Vec2Float pos, const std::vector<EnemyType>& spawnList, EnemyManager& enemyMng);
	~EnemySpawner();
	void Spawn(EnemyType type);	// 敵をスポーン
private:
	Vec2Float pos_;	// 座標
	std::vector<EnemyType>spawnList_;
	EnemyManager* enemyMng_;
};

