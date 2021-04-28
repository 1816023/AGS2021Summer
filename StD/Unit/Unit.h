#pragma once
#include <DxLib.h>
#include "../VECTOR2.h"

// Unitのステータス(共通部分)
struct UnitStat
{
	Vec2Float pos;			// 座標
	float atkSpeed;			// 攻撃速度
	float atkDist;			// 射程
	unsigned int power;		// 攻撃力
	unsigned int life;		// 体力
	bool isDead;			// 死んでいるかどうか
};

// Unit基底クラス
class Unit
{
public:
	Unit() = default;
	virtual ~Unit() = default;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	const Vec2Float GetPosition();
	void SetPosition(Vec2Float pos);
	unsigned int GetHP();
	const bool IsDeath();
protected:
	UnitStat state_;
};

