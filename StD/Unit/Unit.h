#pragma once
#include <DxLib.h>
#include "../VECTOR2.h"

// Unit�̃X�e�[�^�X(���ʕ���)
struct UnitStat
{
	Vec2Float pos;			// ���W
	float atkSpeed;			// �U�����x
	float atkDist;			// �˒�
	unsigned int power;		// �U����
	unsigned int life;		// �̗�
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
	const Vec2Float GetPosition();
	void SetPosition(Vec2Float pos);
	unsigned int GetHP();
	const bool IsDeath();
protected:
	UnitStat state_;
};

