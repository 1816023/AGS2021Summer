#include "UIText.h"
#include <DxLib.h>
#include "../Mng/FontMng.h"

UIText::UIText(VECTOR2 pos, std::wstring str)
{
	pos_ = pos;
	str_ = str;
	fontHandle_ = -1;
}

UIText::UIText(VECTOR2 pos, std::wstring str, int fontSize)
{
	pos_ = pos;
	str_ = str;
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
		DrawString(pos_.x, pos_.y, str_.c_str(), 0xffffff);
		return;
	}
	DrawStringToHandle(pos_.x, pos_.y, str_.c_str(), 0xffffff, fontHandle_);
}
