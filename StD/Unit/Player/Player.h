#pragma once
#include "../Unit.h"

class Player: public Unit
{
public:
	Player() = default;
	~Player() = default;
	void Init();
	void Update(float deltaTime);
	void Draw();
	//virtual void Skill(void)=0;
protected:
	bool isSkill_;	//skill‚ª”­“®‰Â”\‚©
};

