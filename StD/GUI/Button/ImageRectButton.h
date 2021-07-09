#pragma once
#include "Button.h"
class ImageRectButton :
    public Button
{
public:
	ImageRectButton() = default;
	ImageRectButton(VECTOR2 pos, VECTOR2 size, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()>func, VECTOR2 offset = {});
	ImageRectButton(VECTOR2 size, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()>func, VECTOR2 offset = {});
    ~ImageRectButton()override;
	// カーソルがある位置との当たり判定(マウスポジション指定)
	bool IsHit(VECTOR2 mPos)override;
	// ボタンの描画
	void Draw()override;
private:
};

