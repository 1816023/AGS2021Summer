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
	//void Skill(void)override;	//Skillä«óù
private:
};

