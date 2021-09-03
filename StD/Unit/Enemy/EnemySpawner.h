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
	EnemySpawner(Vec2Float pos, EnemyManager& enemyMng, Map& map, int spawnerId);
	~EnemySpawner();
	// �G���X�|�[��
	void Spawn(EnemyData data);
	// �X�V
	void Update(float deltaTime);
	// �c��̓G�̐�
	int GetRemainSpawnCnt();
private:
	Vec2Float pos_;	// ���W
	std::vector<EnemyData>spawnEDatas_;	// �X�|�[������G�̃f�[�^
	EnemyManager* enemyMng_;	// �G�Ǘ��p
	std::vector<std::vector<RootDir>>root_;	// �G�ړ����[�g�̃��X�g
	float cnt_;		// �G�̏o���Ԋu�J�E���^
	int wave_;	// �E�F�[�u
};

