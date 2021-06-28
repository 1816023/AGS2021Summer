#pragma once
#include "BaseScene.h"

class GameOverScene :
	public BaseScene
{
public:
	GameOverScene();
	~GameOverScene();

	unique_Base Update(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::RESULT; }
private:
	void Draw()override;
	void DrawUI()override;
};
