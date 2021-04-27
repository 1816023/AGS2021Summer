#pragma once
#include "BaseScene.h"

class ECircle;
class SlipDamage;

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	unique_Base Update(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::TITLE; }
private:
	void Draw()override;
	void DrawUI()override;
	SlipDamage* slipDamage;
	bool trapFlag;
	int cnt;
	int HP;
};

