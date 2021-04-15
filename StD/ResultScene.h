#pragma once
#include "BaseScene.h"
class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();

	unique_Base UpData(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::RESULT; }
private:
};

