#pragma once
#include <DxLib.h>
#include "../VECTOR2.h"

// Unit�̃X�e�[�^�X(���ʕ���)
struct UnitStat
{
	Vec2Float pos;			// ���W
	float atkSpeed;			// �U���Ԋu
	float atkRange;			// �˒�
	unsigned int power;		// �U����
	int life;		// �̗�
	bool isDead;			// ����ł��邩�ǂ���
};

// Unit���N���X
class Unit
{
public:
	Unit() = default;
	virtual ~Unit() = default;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual const float GetAttackSpan(void);
	virtual const float GetAtkRange(void);
	virtual const Vec2Float GetPos();
	virtual void SetPosition(Vec2Float pos);
	virtual const int GetHP();
	virtual void SetHP(int power);
	virtual unsigned int GetAttackPower(void);
	//void SetDeath(bool flag);
	virtual const bool IsDeath();
protected:
	UnitStat state_;
};

