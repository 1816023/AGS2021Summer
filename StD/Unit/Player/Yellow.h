#pragma once
#include "Player.h"
class Yellow :
	public Player
{
public:
	Yellow();
	~Yellow();
	void Init();
	void Update();
	void Draw();
	void Skill(void)override;	//Skill�Ǘ�
private:
	UnitStat stat_;
};

