#pragma once
#include "Enemy.h"


class ECircle : public Enemy
{
public:
	ECircle();
	ECircle(MapInfo& mapInfo);
	~ECircle();

	void Update(float deltaTime)override;
	void Draw()override;
	Enemy* CreateClone();
private:	
	// --- 各種更新処理 ---
	using Func_t = void (ECircle::*)(float);
	Func_t updater_;
	// 生成直後
	void StartUpdate(float deltaTime);
	// 移動など
	void RunUpdate(float deltaTime);
	
	// 死んだとき
	void deathUpdate(float deltaTime);
	// --------------------
};

