#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "../../VECTOR2.h"
#include "EnemyType.h"

class Enemy;
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
private:
	// 敵を作成する
	Enemy& CreateEnemy(EnemyType type);

	std::vector<std::shared_ptr<Enemy>>enemies_;	// 敵たち
	using Prototype = std::unordered_map<EnemyType, Enemy*>;
	Prototype prototype_;	// 敵のプロトタイプ
};

