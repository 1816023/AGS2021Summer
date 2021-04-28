#pragma once
#include "../Unit.h"

class Player: public Unit
{
public:
	Player() = default;
	~Player() = default;
	void Init();
	virtual void Update(float deltaTime) = 0;
	void Draw();
	virtual Vec2Float GetPos(void);
	virtual float GetBulletSpeed(void);
	virtual float GetAtkRange(void);
	//virtual void Skill(void)=0;
protected:
	int imageID;
	bool isSkill_;	//skill‚ª”­“®‰Â”\‚©
};

