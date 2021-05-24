#pragma once
#include "Button.h"
class RectButton :
    public Button
{
public:
    RectButton(VECTOR2 lu, VECTOR2 rd, int color, std::function<bool()> func, VECTOR2 offset);
    ~RectButton();
	void Update();
	// カーソルがある位置との当たり判定(マウスポジション指定)
	bool IsHit(VECTOR2 mPos);
	// ボタンの描画
	void Draw();

private:
	//const VECTOR2 offset_;
};

