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
	Vec2Float GetPos(void)override;
	float GetBulletSpeed(void)override;
	float GetAtkRange(void)override;
	//void Skill(void)override;	//Skill�Ǘ�
private:
	UnitStat stat_;
};

