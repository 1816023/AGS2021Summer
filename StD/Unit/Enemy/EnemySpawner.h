#pragma once
#include "../../VECTOR2.h"
#include <vector>
#include "EnemyType.h"

// �G�𔭐�������N���X
class Map;
class EnemyManager;
class EnemySpawner
{
friend class EnemyManager;
public:
	EnemySpawner(Vec2Float pos, EnemyManager& enemyMng);
	~EnemySpawner();
	void Spawn(EnemyType type);	// �G���X�|�[��
	void Update(float deltaTime);
private:
	Vec2Float pos_;	// ���W
	std::vector<EnemyType>spawnList_;
	EnemyManager* enemyMng_;
	float cnt_;
	//Map* map_;
	std::vector<RootDir>root_;
};

