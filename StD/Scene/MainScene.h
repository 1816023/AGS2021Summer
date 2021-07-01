#pragma once
#include "BaseScene.h"
#include <list>
class Button;
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
	void DrawUI()override;
	std::list<std::unique_ptr<Button>>button_;
};

