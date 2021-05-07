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
	// �G���X�|�[��
	void Spawn(EnemyType type);	
	// �X�V
	void Update(float deltaTime);
private:
	Vec2Float pos_;	// ���W
	std::vector<EnemyType>spawnList_;	// �X�|�[������G�̎�ނ̃��X�g
	EnemyManager* enemyMng_;	// �G�Ǘ��p
	std::vector<RootDir>root_;	// �G�ړ����[�g�̃��X�g
	float cnt_;		// �G�̏o���Ԋu�J�E���^
};

