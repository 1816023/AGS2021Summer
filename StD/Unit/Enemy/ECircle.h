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
	int rootType;	// ルートの種類
	int rootIdx_;	// ルートのインデックス
	Vec2Float dirVec;		// 移動方向のベクトル
	Vec2Float nowMove_;		// 前回決定してからの移動値
	VECTOR2 mapChipSize;	// マップのチップサイズ
	VECTOR2 mapSize;		// マップのチップ数
	
	// --- 各種更新処理 ---
	using Func_t = void (ECircle::*)(float);
	Func_t updater_;
	// 移動など
	void RunUpdate(float deltaTime);
	// 移動方向の決定をする
	void SearchUpdate(float deltaTime);
	// 死んだとき
	void deathUpdate(float deltaTime);
	// --------------------

	// 移動処理
	void Move(float deltaTime);
};

