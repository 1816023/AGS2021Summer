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
// �G�N���X
class Enemy : public Unit
{
public:
	Enemy();
	Enemy(MapInfo& mapInfo);
	virtual ~Enemy();
	// �X�V
	virtual void Update(float deltaTime);
	// �`��
	virtual void Draw();
	// �N���[���쐻
	virtual Enemy* CreateClone() = 0;
	// ���[�g��ݒ�
	void SetRoot(std::vector<RootDir>& root);
	// �X�s�[�h���擾
	const float GetSpeed();
	// �X�s�[�h�ݒ�
	void SetSpeed(float speed);
protected:
	// �G�݂̂̏��
	struct EnemyInfo
	{
		std::vector<RootDir> root;	// �ړ����[�g
		VECTOR2 mapChipSize;	// �}�b�v�̃`�b�v�T�C�Y
		VECTOR2 mapSize;		// �}�b�v�̃`�b�v��	
		Vec2Float dirVec;		// �ړ������̃x�N�g��
		Vec2Float nowMove;		// �O�񌈒肵�Ă���̈ړ��l
		float speed;			// �ړ����x
		float scale;			// �傫��
		int rootIdx;			// ���[�g�̃C���f�b�N�X
	};
	// �ړ�����
	void Move(float deltaTime);
	// �ړ������̌��������
	void SearchRoot(float deltaTime);
	
	EnemyInfo enemyInfo_;	// �G�̏��
};

