#pragma once
#include "CustomState.h"
#include "../Scene/CustomMapScene.h"
//#include "../Unit/Enemy/Enemy.h"

#define CUSTOM dynamic_cast<Custom*>(scene->map_.get())

struct EnemyCustom :public CustomStateBase
{
	EnemyCustom(){};
	~EnemyCustom() {};
	bool Init(CustomMapScene* scene)
	{
		return false;
	}
	void Update(CustomMapScene* scene)
	{

	}

	void Draw(CustomMapScene* scene)
	{

	}
	void Delete() {
	}
};