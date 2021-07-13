#pragma once
#include "Button.h"
class RoundRectButton:
	public Button
{
public:
	RoundRectButton(VECTOR2 lu, VECTOR2 size, VECTOR2 radius, int color, std::function<bool()>func, VECTOR2 offset);
	RoundRectButton(VECTOR2 size, VECTOR2 radius, int color, std::function<bool()>func, VECTOR2 offset);
	~RoundRectButton()override;
	// カーソルがある位置との当たり判定(マウスポジション指定)
	bool IsHit(VECTOR2 mPos)override;
	// ボタンの描画
	void Draw()override;
private:

};

