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
	Vec2Float GetPos(void)override;
	float GetBulletSpeed(void)override;
	float GetAtkRange(void)override;
	//void Skill(void)override;	//Skillä«óù
private:
	UnitStat stat_;
};

