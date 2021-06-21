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
		astar_ = std::make_unique<Astar>(*scene->cusMap_);
		const auto& spawners = scene->cusMap_->Getspawner();
		const auto& mainStay = scene->cusMap_->GetMainStay();
		if (mainStay != VECTOR2(-1, -1) && spawners.size() != 0)
		{
			astar_->AstarStart(mainStay, spawners.at(0));
		}
		spawner_= scene->cusMap_->Getspawner();
		return true;
	}
	void Update(CustomMapScene* scene)
	{

	}

	void Draw(CustomMapScene* scene)
	{

	}
	void Delete() {
	}
	// Astarクラスのポインター
	std::unique_ptr<Astar>astar_;
	std::map<int, VECTOR2>spawner_;
};