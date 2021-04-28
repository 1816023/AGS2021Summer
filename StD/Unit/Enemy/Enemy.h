#pragma once
#include "../Unit.h"
#include "../../VECTOR2.h"
#include "EnemyType.h"
#include <vector>

// �p�����[�^�萔
// HP
#define LOW_HP 60		
#define MID_HP 120
#define HIGH_HP 180
// �U����
#define LOW_ATK 1
#define MID_ATK 2
#define HIGH_ATK 3
// �˒�
#define LOW_DIST 10
#define MID_DIST 20
#define HIGH_DIST 30
// ���x
#define LOW_SPEED 5
#define MID_SPEED 10
#define HIGH_SPEED 15

// �傫��
#define E_SIZE_X 64
#define E_SIZE_Y 64

// �}�b�v���(�K�v�Ȃ���)
struct MapInfo
{
	VECTOR2 chipSize;	// 1�`�b�v�̑傫��
	VECTOR2 mapSize;	// �}�b�v�̃`�b�v��
};



class Map;
class Enemy : public Unit
{
public:
	Enemy();
	Enemy(MapInfo& mapInfo);
	virtual ~Enemy();
	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual Enemy* CreateClone() = 0;
	unsigned int GetHP();
	Vec2Float GetPosition();
	void SetPosition(Vec2Float pos);
	void SetRoot(std::vector<RootDir>& root);
	bool IsDeath();
	const float GetSpeed();
	void SetSpeed(float speed);
protected:
	struct EnemyInfo
	{
		std::vector<RootDir> root;
		float scale;
		VECTOR2 mapChipSize;	// �}�b�v�̃`�b�v�T�C�Y
		VECTOR2 mapSize;		// �}�b�v�̃`�b�v��
		int rootIdx;	// ���[�g�̃C���f�b�N�X
		Vec2Float dirVec;		// �ړ������̃x�N�g��
		Vec2Float nowMove;		// �O�񌈒肵�Ă���̈ړ��l
		float speed;
	};
	// �ړ�����
	void Move(float deltaTime);
	// �ړ������̌��������
	void SearchRoot(float deltaTime);
	
	EnemyInfo enemyInfo_;
};

