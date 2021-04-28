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
	float GetBulletSpeed(void)override;
	float GetAtkRange(void)override;
	//void Skill(void)override;	//Skill�Ǘ�
private:
	UnitStat stat_;
};

