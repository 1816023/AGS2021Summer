#pragma once
#include "PlayerType.h"
#include "../Unit.h"

class Player: public Unit
{
public:
	Player() = default;
	~Player() = default;
	void Init();
	virtual void Update(float deltaTime) = 0;
	virtual int GetSpawnCost(void) = 0;		//�������ɕK�v�ƂȂ�cost�̎擾
	void Draw();
	virtual void Skill(void)=0;
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
protected:
	PlayerUnit id;
	AttackType type;
	int imageID;
	float coolTime_;	//skill�Ďg�p�܂ł̎���
	bool isSkill_;	//skill�������\��
	bool executable; //���s�\��
	PlayerUnit UnitID;
private:
};

