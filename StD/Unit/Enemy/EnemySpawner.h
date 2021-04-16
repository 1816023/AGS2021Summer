#pragma once
#include "../../VECTOR2.h"
#include <vector>
#include "EnemyType.h"

// �G�𔭐�������N���X
class EnemyManager;
class EnemySpawner
{
friend class EnemyManager;
public:
	EnemySpawner(Vec2Float pos, const std::vector<EnemyType>& spawnList, EnemyManager& enemyMng);
	~EnemySpawner();
	void Spawn(EnemyType type);	// �G���X�|�[��
private:
	Vec2Float pos_;	// ���W
	std::vector<EnemyType>spawnList_;
	EnemyManager* enemyMng_;
};

