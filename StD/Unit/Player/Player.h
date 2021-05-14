#pragma once
#include "../Unit.h"

class Player: public Unit
{
public:
	Player() = default;
	~Player() = default;
	void Init();
	virtual void Update(float deltaTime) = 0;
	virtual int GetSpawnCost(void) = 0;		//召喚時に必要となるcostの取得
	void Draw();
	//virtual void Skill(void)=0;
protected:
	int imageID;
	bool isSkill_;	//skillが発動可能か
private:
};

