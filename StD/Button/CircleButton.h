#pragma once
#include "Button.h"
class CircleButton :
    public Button
{
public:
    CircleButton(VECTOR2 pos, int radius, int color, std::function<bool()>func, VECTOR2 offset);
    ~CircleButton();

	void Update();
	// カーソルがある位置との当たり判定(マウスポジション指定)
	bool IsHit(VECTOR2 mPos);
	// ボタンの描画
	void Draw();
private:
};

