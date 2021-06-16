#pragma once
#include "CustomState.h"
#include "../Scene/CustomMapScene.h"
#define CUSTOM dynamic_cast<Custom*>(scene->cusMap_.get())

struct EndCustom :CustomStateBase
{
	EndCustom() {};
	~EndCustom() {};
	bool Init(CustomMapScene* scene)override
	{
		return false;
	}
	void Update(CustomMapScene* scene)override
	{
		if ((scene->now[KEY_INPUT_BACK]) & (~scene->old[KEY_INPUT_BACK]))
		{
			scene->nowState_ = CustomState::SELECT_FILE;
			scene->custom_[scene->nowState_]->Init(scene);
			Delete();
		}
		if ((scene->now[KEY_INPUT_RETURN]) & (~scene->old[KEY_INPUT_RETURN]))
		{
			CUSTOM->SaveFile();
		}

	}

	void Draw(CustomMapScene* scene)override
	{

	}
	void Delete() {
	}
};