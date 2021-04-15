#pragma once
#include "BaseScene.h"
class MainScene :
	public BaseScene
{
public:
	MainScene();
	~MainScene();

	unique_Base Update(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::MAIN; }
private:
	void Draw()override;
};

