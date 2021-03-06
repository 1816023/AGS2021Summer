#pragma once
#include "Button.h"
class CircleButton :
    public Button
{
public:
    CircleButton(VECTOR2 pos, int radius, int color, std::function<bool()>func);
	// 座標を決めないで作成(キャンパス追加用)
	CircleButton(int radius, int color, std::function<bool()>func);
    ~CircleButton()override;
	// カーソルがある位置との当たり判定(マウスポジション指定)
	bool IsHit(VECTOR2 mPos)override;
	// ボタンの描画
	void Draw()override;
private:
};

