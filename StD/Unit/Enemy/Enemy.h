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
#define LOW_SPEED 10
#define MID_SPEED 20
#define HIGH_SPEED 30

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
	virtual unsigned int GetHP();
	virtual void SetPosition(Vec2Float pos);
	virtual void SetRoot(std::vector<RootDir>& root);
	bool IsDeath();
protected:
	std::vector<RootDir> root_;
	float scale_;
};

