#pragma once
#include "BaseScene.h"
class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	unique_Base Update(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::GAME; }
private:
	void Draw()override;
};

