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
// “GŠÇ—ƒNƒ‰ƒX
class EnemyManager
{
friend class EnemySpawner;
public:
	EnemyManager(Map& map);
	~EnemyManager();
	// XV
	void Update(float deltaTime);	
	// •`‰æ
	void Draw();	
	// “GƒŠƒXƒg‚ğæ“¾(‚·‚×‚Ä‚Ì“G)
	EnemyList& GetEnemies();
	// €–S‚µ‚½“G‚Ìíœ
	void Killer(std::shared_ptr<Enemy> enemy);
private:
	// “G‚ğì¬‚·‚é
	Enemy& CreateEnemy(EnemyType type);

	EnemyList enemies_;	// “GƒŠƒXƒg
	using Prototype = std::unordered_map<EnemyType, Enemy*>;
	Prototype prototype_;	// “G‚Ìƒvƒƒgƒ^ƒCƒv
	std::unique_ptr<ShotMng> shotMng_;
};

