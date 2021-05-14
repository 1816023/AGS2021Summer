#pragma once
#include "Player.h"
class Blue :
	public Player
{
public:
	Blue();
	Blue(Vec2Float pos);
	~Blue();
	void Init();
	void Update(float deltaTime);
	void Draw();
	int GetSpawnCost(void);
	//void Skill(void)override;	//Skillä«óù
private:
};

