#include "UIText.h"
#include <DxLib.h>
#include "../Mng/FontMng.h"

UIText::UIText(VECTOR2 pos, std::wstring str, int color)
{
	pos_ = pos;
	str_ = str;
	color_ = color;
	fontHandle_ = -1;
}

UIText::UIText(VECTOR2 pos, std::wstring str, int fontSize, int color)
{
	pos_ = pos;
	str_ = str;
	color_ = color;
	fontHandle_ = lpFontMng.AddStrFont(fontSize, std::to_wstring(fontSize));
}

bool UIText::Update()
{
	return false;
}

void UIText::Draw()
{
	if (fontHandle_ == -1)
	{
		DrawString(pos_.x, pos_.y, str_.c_str(), color_);
		return;
	}
	DrawStringToHandle(pos_.x, pos_.y, str_.c_str(), color_, fontHandle_);
}

void UIText::SetText(std::wstring str)
{
	str_ = str;
}

void UIText::SetColor(int color)
{
	color_ = color;
}
