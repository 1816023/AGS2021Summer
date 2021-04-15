#pragma once
#include "BaseScene.h"
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	unique_Base UpData(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::TITLE; }
private:
	void Draw()override;
};

