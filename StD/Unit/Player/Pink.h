#pragma once
#include "Player.h"
class Pink :
	public Player
{
public:
	Pink();
	Pink(Vec2Float pos);
	~Pink();
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

