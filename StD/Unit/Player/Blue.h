#pragma once
#include "Player.h"
class Blue :
	public Player
{
public:
	Blue();
	Blue(Vec2Float pos, AttackType type);
	~Blue();
	void Init();
	void Draw(); 
	void Skill(void);
	int GetSpawnCost(void);
	//void Skill(void)override;	//Skillä«óù
private:
};

