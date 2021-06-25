#pragma once
#include "../Enemy.h"
class ETriangle : public Enemy
{
public:
	ETriangle();
	ETriangle(MapInfo& mapInfo);
	~ETriangle();

	// 更新
	void Update(float deltaTime)override;
	// 描画
	void Draw()override;
	// クローン作製
	Enemy* CreateClone()override;
private:
	// --- 各種更新処理 ---
	using Func_t = void (ETriangle::*)(float);
	Func_t updater_;
	// 生成直後
	void StartUpdate(float deltaTime);
	// 移動など
	void RunUpdate(float deltaTime);
	// 死んだとき
	void deathUpdate(float deltaTime);
	// --------------------
};

