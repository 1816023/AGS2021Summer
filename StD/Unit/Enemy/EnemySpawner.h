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
	// 敵をスポーン
	void Spawn(EnemyType type);	
	// 更新
	void Update(float deltaTime);
private:
	Vec2Float pos_;	// 座標
	std::vector<EnemyType>spawnList_;	// スポーンする敵の種類のリスト
	EnemyManager* enemyMng_;	// 敵管理用
	std::vector<RootDir>root_;	// 敵移動ルートのリスト
	float cnt_;		// 敵の出現間隔カウンタ
};

