#pragma once
#include "Player.h"
class Pink :
	public Player
{
public:
	Pink();
	Pink(Vec2Float pos, AttackType type);
	~Pink();
	void Init();
	void Update(float deltaTime);
	void Draw();
	int GetSpawnCost(void);
	void Skill(void)override;	//Skillä«óù
private:
};

