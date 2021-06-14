#pragma once
#include "BaseScene.h"
#include "../VECTOR2.h"

class ECircle;
class PlayerMng;

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

	bool trapFlag;
	int cnt;
	int HP;
	Vec2Float pos;
	float speed;
};

