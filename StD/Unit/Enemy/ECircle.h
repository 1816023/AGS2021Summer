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
	// --- ŠeíXVˆ— ---
	using Func_t = void (ECircle::*)(float);
	Func_t updater_;
	// ¶¬’¼Œã
	void StartUpdate(float deltaTime);
	// ˆÚ“®‚È‚Ç
	void RunUpdate(float deltaTime);
	
	// €‚ñ‚¾‚Æ‚«
	void deathUpdate(float deltaTime);
	// --------------------
};

