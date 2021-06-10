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
// �G�Ǘ��N���X
class EnemyManager
{
friend class EnemySpawner;
public:
	EnemyManager(Map& map);
	~EnemyManager();
	// �X�V
	void Update(float deltaTime);	
	// �`��
	void Draw();	
	// �G���X�g���擾(���ׂĂ̓G)
	EnemyList& GetEnemies();
private:
	// �G���쐬����
	Enemy& CreateEnemy(EnemyType type);

	EnemyList enemies_;	// �G���X�g
	using Prototype = std::unordered_map<EnemyType, Enemy*>;
	Prototype prototype_;	// �G�̃v���g�^�C�v
	std::unique_ptr<ShotMng> shotMng_;
};

