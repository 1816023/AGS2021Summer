#include "UIText.h"
#include <DxLib.h>

UIText::UIText(VECTOR2 pos, std::wstring str, int fontSize)
{
	pos_ = pos;
	str_ = str;

}

bool UIText::Update()
{
	return false;
}

void UIText::Draw()
{
	DrawString(pos_.x, pos_.y, L"", 0xffffff);
}
