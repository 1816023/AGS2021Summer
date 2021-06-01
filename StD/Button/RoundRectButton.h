#pragma once
#include "Button.h"
class RoundRectButton:
	public Button
{
public:
	RoundRectButton(VECTOR2 lu, VECTOR2 rd, VECTOR2 radius, int color, std::function<bool()>func, VECTOR2 offset);
	~RoundRectButton();
	// カーソルがある位置との当たり判定(マウスポジション指定)
	bool IsHit(VECTOR2 mPos);
	// ボタンの描画
	void Draw();
private:

};

