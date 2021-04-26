#pragma once
#include "Enemy.h"

class ECircle : public Enemy
{
public:
	ECircle();
	~ECircle();

	void Update(float deltaTime)override;
	void Draw()override;
	Enemy* CreateClone();
private:
	int rootIdx_;	// ルートのインデックス
	using Func_t = void (ECircle::*)(float);
	Func_t updater;
	void RunUpdate(float deltaTime);
	void SearchUpdate(float deltaTime);
	void deathUpdate(float deltaTime);
};

