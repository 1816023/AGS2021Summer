#pragma once
#include "Button.h"
class ImageCircleButton :
    public Button
{
public:
    ImageCircleButton(VECTOR2 pos, int radius, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()>func, VECTOR2 offset);
    ~ImageCircleButton();
	void Update();
	// カーソルがある位置との当たり判定(マウスポジション指定)
	bool IsHit(VECTOR2 mPos);
	// ボタンの描画
	void Draw();
private:
};

