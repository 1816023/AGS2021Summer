#pragma once
#include <DxLib.h>

// Unitのステータス(共通部分)
struct UnitStat
{
	unsigned int power;		// 攻撃力
	unsigned int life;		// 体力
	float atkSpeed;			// 攻撃速度
	float atkDist;			// 射程
};

// Unit基底クラス
class Unit
{
public:
	Unit() = default;
	virtual ~Unit() = default;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
protected:
	UnitStat state_;
};

