#pragma once
#include "Player.h"
class Yellow :
	public Player
{
public:
	Yellow();
	Yellow(Vec2Float pos, AttackType type);
	~Yellow();
	void Init();
	void Draw();
	void Skill(void);
	int GetSpawnCost(void);
	//void Skill(void)override;	//Skillä«óù
private:
};

