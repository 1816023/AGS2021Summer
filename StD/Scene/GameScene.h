#pragma once
#include "BaseScene.h"
#include "../Map/Map.h"
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
	//デバッグ
	std::unique_ptr<Map> map;
	
};

