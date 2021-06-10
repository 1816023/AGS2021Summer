#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "../../VECTOR2.h"
#include "EnemyType.h"

class Enemy;
using EnemyList = std::vector<std::shared_ptr<Enemy>>;

class ShotMng;
class Map;
// 敵管理クラス
class EnemyManager
{
friend class EnemySpawner;
public:
	EnemyManager(Map& map);
	~EnemyManager();
	// 更新
	void Update(float deltaTime);	
	// 描画
	void Draw();	
	// 敵リストを取得(すべての敵)
	EnemyList& GetEnemies();
private:
	// 敵を作成する
	Enemy& CreateEnemy(EnemyType type);

	EnemyList enemies_;	// 敵リスト
	using Prototype = std::unordered_map<EnemyType, Enemy*>;
	Prototype prototype_;	// 敵のプロトタイプ
	std::unique_ptr<ShotMng> shotMng_;
};

