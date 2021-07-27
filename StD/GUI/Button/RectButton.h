#pragma once
#include "Button.h"
class RectButton :
    public Button
{
public:
    RectButton(VECTOR2 pos, VECTOR2 size, int color, std::function<bool()> func);
    ~RectButton()override;
	// カーソルがある位置との当たり判定(マウスポジション指定)
	bool IsHit(VECTOR2 mPos)override;
	// ボタンの描画
	void Draw()override;

private:
	//const VECTOR2 offset_;
};

