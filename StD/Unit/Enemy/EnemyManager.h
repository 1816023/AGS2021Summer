#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "../../VECTOR2.h"
#include "EnemyType.h"

class Enemy;

using Prototype = std::unordered_map<EnemyType, Enemy*>;

// “GŠÇ—ƒNƒ‰ƒX
class EnemyManager
{
friend class EnemySpawner;
public:
	EnemyManager();
	
	void Update(float deltaTime);
	void Draw();
private:
	// “G‚ğì¬‚·‚é
	Enemy& CreateEnemy(EnemyType type);

	std::vector<std::unique_ptr<Enemy>>enemies_;
	Prototype prototype_;

};

