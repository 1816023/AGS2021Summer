#pragma once
#include "CustomState.h"
#include "../Scene/CustomMapScene.h"
#define CUSTOM dynamic_cast<Custom*>(scene->map_.get())

struct EndCustom :CustomStateBase
{
	EndCustom() {};
	~EndCustom() {};
	bool Init(CustomMapScene* scene)
	{
		return false;
	}
	void Update(CustomMapScene* scene)
	{
		if ((scene->now[KEY_INPUT_BACK]) & (~scene->old[KEY_INPUT_BACK]))
		{
			scene->nowState_ = CustomState::SET_STATE;
			scene->custom_[scene->nowState_]->Init(scene);

		}
		if ((scene->now[KEY_INPUT_RETURN]) & (~scene->old[KEY_INPUT_RETURN]))
		{
			CUSTOM->SaveFile();
		}

	}

	void Draw(CustomMapScene* scene)
	{

	}
};