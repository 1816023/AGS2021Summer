#pragma once
#include "Player.h"
class Green :
	public Player
{
public:
	Green();
	Green(Vec2Float pos);
	~Green();
	void Init();
	void Update(float deltaTime);
	void Draw();
	//void Skill(void)override;	//Skillä«óù
private:
	UnitStat stat_;
};

