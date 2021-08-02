#include <DxLib.h>
#include "../../Mng/ImageMng.h"
#include "../../StringUtil.h"
#include "RectButton.h"

RectButton::RectButton(VECTOR2 pos, VECTOR2 size, int color, std::function<bool()> func)
{
	lu_ = pos;
	rd_ = pos + size;
	color_ = color;
	func_ = func;
	type_ = ButtonType::Rect;

}

RectButton::~RectButton()
{
}


bool RectButton::IsHit(VECTOR2 mPos)
{
	if (!((mPos.x < lu_.x || mPos.y < lu_.y) || (mPos.x<lu_.x || mPos.y>rd_.y) || (mPos.x > rd_.x || mPos.y < lu_.y) || (mPos.x > rd_.x || mPos.y > rd_.y)))
	{
		isPush_ = true;
		return true;
	}
	else
	{
		isPush_ = false;
		return false;
	}

}

void RectButton::Draw()
{
	const int shadow = 3;
	const int push = 1;
	if (isPush_)
	{
		DrawBox(lu_.x + push, lu_.y + push, rd_.x + push, rd_.y + push, color_, true);
		if (fontHandle_ != -1)
		{
			DrawStringToHandle(lu_.x + sPos_.x + push, lu_.y + sPos_.y + push, _StW(str_).c_str(), ~color_, fontHandle_);
		}
		else {
			DrawString(lu_.x + sPos_.x + push, lu_.y + sPos_.y + push, _StW(str_).c_str(), ~color_);

		}
	}
	else
	{
		DrawBox(lu_.x + shadow, lu_.y + shadow, rd_.x + shadow, rd_.y + shadow, 0x000000, true);
		DrawBox(lu_.x, lu_.y, rd_.x, rd_.y, color_, true);
		if (fontHandle_ != -1)
		{
			DrawStringToHandle(lu_.x + sPos_.x, lu_.y + sPos_.y, _StW(str_).c_str(), ~color_, fontHandle_);
		}
		else {
			DrawString(lu_.x + sPos_.x, lu_.y + sPos_.y, _StW(str_).c_str(), ~color_);

		}
	}

}
