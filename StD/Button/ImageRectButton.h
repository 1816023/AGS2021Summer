#pragma once
#include "Button.h"
class ImageRectButton :
    public Button
{
public:
    ImageRectButton(VECTOR2 pos, VECTOR2 size, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()>func, VECTOR2 offset);
    ~ImageRectButton();
	void Update();
	// カーソルがある位置との当たり判定(マウスポジション指定)
	bool IsHit(VECTOR2 mPos);
	// ボタンの描画
	void Draw();
private:
};

