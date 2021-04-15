#pragma once
#include <DxLib.h>

// Unit�̃X�e�[�^�X(���ʕ���)
struct UnitStat
{
	unsigned int power;		// �U����
	unsigned int life;		// �̗�
	float atkSpeed;			// �U�����x
	float atkDist;			// �˒�
};

// Unit���N���X
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

