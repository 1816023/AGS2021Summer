#pragma once
#include "Enemy.h"


class ECircle : public Enemy
{
public:
	ECircle();
	ECircle(Map& map);
	~ECircle();

	void Update(float deltaTime)override;
	void Draw()override;
	Enemy* CreateClone();
private:
	int rootType;	// ルートの種類
	int rootIdx_;	// ルートのインデックス
	Vec2Float move_;
	Vec2Float nowMove_;
	VECTOR2 mapChipSize;
	VECTOR2 mapSize;
	
	using Func_t = void (ECircle::*)(float);
	Func_t updater_;
	void RunUpdate(float deltaTime);
	void SearchUpdate(float deltaTime);
	void deathUpdate(float deltaTime);
};

