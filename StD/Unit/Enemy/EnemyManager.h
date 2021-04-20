#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "../../VECTOR2.h"
#include "EnemyType.h"

class Enemy;

// 敵管理クラス
class EnemyManager
{

friend class EnemySpawner;
public:
	static EnemyManager& Instance()
	{
		static EnemyManager app;
		return app;
	}
	~EnemyManager();
	
	void Update(float deltaTime);
	void Draw();
private:
	EnemyManager();
	EnemyManager(const EnemyManager&) = delete;
	EnemyManager operator=(const EnemyManager&) = delete;
	using Prototype = std::unordered_map<EnemyType, Enemy*>;
	// 敵を作成する
	Enemy& CreateEnemy(EnemyType type);

	std::vector<std::shared_ptr<Enemy>>enemies_;
	Prototype prototype_;

};

