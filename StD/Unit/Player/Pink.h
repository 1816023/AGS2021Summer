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
	//void Skill(void)override;	//Skill�Ǘ�
private:
	UnitStat stat_;
};

