#pragma once
#include "../Unit.h"

class Player: public Unit
{
public:
	Player() = default;
	~Player() = default;
	void Init();
	void Update(float deltaTime)override;
	void Draw()override;
	virtual void Skill(void)=0;
protected:
	bool isSkill_;	//skillが発動可能か
};

