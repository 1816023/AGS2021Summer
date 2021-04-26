#pragma once
#include "../Unit.h"
#include "../../VECTOR2.h"
#include "EnemyType.h"
#include <vector>

// �p�����[�^�萔
// HP
#define LowHP 1			
#define MidHP 2
#define HighHP 3
// �U����
#define LowAtk 1
#define MidAtk 2
#define HighHP 3
// �˒�
#define LowDist 10
#define MidDist 20
#define HighDist 30
// ���x
#define LowSpeed 10
#define MidDist 20
#define HighDist 30

class Map;
class Enemy : public Unit
{
public:
	Enemy();
	Enemy(Map& map);
	virtual ~Enemy();
	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual Enemy* CreateClone() = 0;
	virtual void SetPosition(Vec2Float pos);
	virtual void SetRoot(std::vector<RootDir>& root);
protected:
	virtual bool IsDeath();
	std::vector<RootDir> root_;
	Map* map_;
	bool isDeath_;
};

