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
	EnemySpawner(Vec2Float pos, EnemyManager& enemyMng, Map& map, int spawnerId);
	~EnemySpawner();
	// 敵をスポーン
	void Spawn(EnemyData data);
	// 更新
	void Update(float deltaTime);
	// 残りの敵の数
	int GetRemainSpawnCnt();
private:
	Vec2Float pos_;	// 座標
	std::vector<EnemyData>spawnEDatas_;	// スポーンする敵のデータ
	EnemyManager* enemyMng_;	// 敵管理用
	std::vector<std::vector<RootDir>>root_;	// 敵移動ルートのリスト
	float cnt_;		// 敵の出現間隔カウンタ
	int wave_;	// ウェーブ
};

