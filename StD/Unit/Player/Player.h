#pragma once
#include <string>
#include <list>
#include "PlayerType.h"
#include "../Unit.h"

struct UnitData
{
	const TCHAR* name;
	int imageId;
	int lv;
	int cost;
	UnitStat stat;
};

class PlayerMng;
class Player: public Unit
{
public:
	Player() = default;
	~Player() = default;
	void Init();
	virtual void Update(float deltaTime);
	virtual int GetSpawnCost(void) = 0;		//�������ɕK�v�ƂȂ�cost�̎擾

	virtual void StatusDraw(Vec2Float pos);
	void Draw();
	virtual void Skill(void)=0;

	virtual void LevelShift(int num);
	void SetExecutable(bool flag);
	void SetStatusOpen(bool flag);

	virtual void SetPosition(Vec2Float pos);
	virtual void SetHP(int power);

	virtual const float GetAttackSpan(void)
	{
		return unitData.stat.atkSpeed;
	};
	virtual const float GetAtkRange(void)
	{
		return unitData.stat.atkRange;
	};
	virtual const Vec2Float GetPos(void)
	{
		return unitData.stat.pos;
	};
	virtual const int GetHP(void)
	{
		return unitData.stat.life;
	};
	virtual unsigned int GetAttackPower(void) 
	{
		return unitData.stat.power;
	};
	const int& GetLevelUpCost()
	{
		return unitData.cost;
	};
	const PlayerUnit& GetID()
	{
		return UnitID;
	};
	const AttackType& GetType()
	{
		return type;
	}
	virtual const bool IsDeath() 
	{
		return unitData.stat.isDead;
	};
	bool isExecutable()
	{
		return executable;
	}
	bool isStatusOpen()
	{
		return statusOpen;
	}
	int GetCoolTime()
	{
		return coolTime_;
	}
protected:
	PlayerMng* player_;
	PlayerUnit id;
	AttackType type;
	float coolTime_;	//skill�Ďg�p�܂ł̎���
	bool isSkill_;	//skill�������\��
	bool executable; //���s�\��
	bool statusOpen = false;	//status��ʂ��J����
	UnitData unitData;
	PlayerUnit UnitID;
private:
};

