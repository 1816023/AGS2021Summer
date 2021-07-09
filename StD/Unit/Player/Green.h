#pragma once
#include "Player.h"
class Green :
	public Player
{
public:
	Green();
	Green(Vec2Float pos, AttackType type);
	~Green();
	void Init();
	void Draw(); 
	void Skill(void);
	int GetSpawnCost(void);
private:
	int defaultPower_;	//’Êí‚Ì‰Î—Í
};

