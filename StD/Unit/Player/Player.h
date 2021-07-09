#pragma once
#include <string>
#include <list>
#include "PlayerType.h"
#include "../Unit.h"

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

	void SetExecutable(bool flag);

	const PlayerUnit& GetID()
	{
		return UnitID;
	};
	const AttackType& GetType()
	{
		return type;
	}
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
	int imageID;
	float coolTime_;	//skill再使用までの時間
	bool isSkill_;	//skillが発動可能か
	bool executable; //実行可能か
	PlayerUnit UnitID;
private:
};

