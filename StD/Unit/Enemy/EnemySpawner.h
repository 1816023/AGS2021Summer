#pragma once
#include "../../VECTOR2.h"
#include <vector>
#include "EnemyType.h"

// 敵を発生させるクラス
class Map;
class EnemyManager;
class EnemySpawner
{
friend class EnemyManager;
public:
	EnemySpawner(Vec2Float pos, EnemyManager& enemyMng);
	~EnemySpawner();
	void Spawn(EnemyType type);	// 敵をスポーン
	void Update(float deltaTime);
private:
	Vec2Float pos_;	// 座標
	std::vector<EnemyType>spawnList_;
	EnemyManager* enemyMng_;
	float cnt_;
	//Map* map_;
	std::vector<RootDir>root_;
};

