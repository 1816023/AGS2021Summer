#pragma once
#include "BaseScene.h"

class PlayerMng;
class ResultScene :
	public BaseScene
{
public:
	ResultScene(bool _flag);
	~ResultScene();

	unique_Base Update(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::RESULT; }
private:
	void Draw()override;
	void DrawUI()override;
	std::unique_ptr<PlayerMng> player_;

	int winImage;
	int loseImage;
	int timeImage;
	int bestImage;
	int number[11];

	bool flag;
	bool resultFlag;
	int time;
	int second;
	int minute;
};

