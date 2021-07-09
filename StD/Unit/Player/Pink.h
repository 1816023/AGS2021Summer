#pragma once
#include "Player.h"

class PlayerMng;
class Pink :
	public Player
{
public:
	Pink();
	Pink(Vec2Float pos, AttackType type,PlayerMng* mng_);
	~Pink();
	void Init();
	void Draw();
	int GetSpawnCost(void);
	void Skill(void)override;	//Skillä«óù
private:
};

