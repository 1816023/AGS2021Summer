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
	virtual int GetSpawnCost(void) = 0;		//召喚時に必要となるcostの取得
	void Draw();
	virtual void Skill(void)=0;

	virtual void LevelShift(int num);
	void SetExecutable(bool flag);

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
	int GetCoolTime()
	{
		return coolTime_;
	}
protected:
	PlayerMng* player_;
	PlayerUnit id;
	AttackType type;
	float coolTime_;	//skill再使用までの時間
	bool isSkill_;	//skillが発動可能か
	bool executable; //実行可能か
	UnitData unitData;
	PlayerUnit UnitID;
private:
};

