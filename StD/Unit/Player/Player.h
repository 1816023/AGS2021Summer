#pragma once
#include "../Unit.h"

class Player: public Unit
{
public:
	Player() = default;
	~Player() = default;
	void Init();
	virtual void Update(float deltaTime) = 0;
	virtual int GetSpawnCost(void) = 0;		//¢Š«‚É•K—v‚Æ‚È‚écost‚Ìæ“¾
	void Draw();
	//virtual void Skill(void)=0;
protected:
	int imageID;
	bool isSkill_;	//skill‚ª”­“®‰Â”\‚©
private:
};

