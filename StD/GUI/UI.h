#pragma once
#include "../VECTOR2.h"
// UI基底クラス
class UI
{
public:
	UI() = default;
	~UI() = default;
	virtual bool Update() = 0;
	// ボタンの描画
	virtual void Draw() = 0;
	VECTOR2 GetPos();
	void SetPos(const VECTOR2& pos);
	VECTOR2 GetSize();
protected:
	// 座標
	VECTOR2 pos_;
	// 座標
	VECTOR2 size_;
};

