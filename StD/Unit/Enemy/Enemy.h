#pragma once
#include "../Unit.h"
#include "../../VECTOR2.h"
#include "EnemyType.h"

// パラメータ定数
// HP
#define LowHP 1			
#define MidHP 2
#define HighHP 3
// 攻撃力
#define LowAtk 1
#define MidAtk 2
#define HighHP 3
// 射程
#define LowDist 10
#define MidDist 20
#define HighDist 30
// 速度
#define LowSpeed 10
#define MidDist 20
#define HighDist 30
class Enemy : public Unit
{
public:
	Enemy();
	virtual ~Enemy();
	virtual void Update(float deltaTime)override;
	virtual void Draw()override;
	virtual void SetPosition(Vec2Float pos);
	virtual Enemy* CreateClone() = 0;
protected:
	virtual bool IsDeath();
	bool isDeath_;
};

