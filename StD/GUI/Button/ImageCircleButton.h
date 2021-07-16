#pragma once
#include "Button.h"
class ImageCircleButton :
    public Button
{
public:
    ImageCircleButton(VECTOR2 pos, int radius, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()>func, VECTOR2 offset);
	ImageCircleButton(int radius, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()>func, VECTOR2 offset);
    ~ImageCircleButton()override;
	// カーソルがある位置との当たり判定(マウスポジション指定)
	bool IsHit(VECTOR2 mPos)override;
	// ボタンの描画
	void Draw()override;
private:
};

