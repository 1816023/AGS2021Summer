#pragma once
#include "Player.h"
class Yellow :
	public Player
{
public:
	Yellow();
	Yellow(Vec2Float pos);
	~Yellow();
	void Init();
	void Update(float deltaTime);
	void Draw();
	Vec2Float GetPos(void)override;
	//void Skill(void)override;	//Skillä«óù
private:
	UnitStat stat_;
};

