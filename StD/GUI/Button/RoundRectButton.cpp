#include <DxLib.h>
#include "../../Mng/ImageMng.h"
#include "../../StringUtil.h"
#include "RoundRectButton.h"

RoundRectButton::RoundRectButton(VECTOR2 lu, VECTOR2 size, VECTOR2 radius, int color, std::function<bool()> func)
{
	pos_ = lu;
	size_ = size;
	radius2_ = radius;
	color_ = color;
	func_ = func;
	type_ = ButtonType::RoundRect;

}

RoundRectButton::RoundRectButton(VECTOR2 size, VECTOR2 radius, int color, std::function<bool()> func)
{
	size_ = size;
	radius2_ = radius;
	color_ = color;
	func_ = func;
	type_ = ButtonType::RoundRect;
}

RoundRectButton::~RoundRectButton()
{
}


bool RoundRectButton::IsHit(VECTOR2 mPos)
{
	auto rd = pos_ + size_;
	if (!((mPos.x < pos_.x || mPos.y < pos_.y) || (mPos.x<pos_.x || mPos.y>rd.y) || (mPos.x > rd.x || mPos.y < pos_.y) || (mPos.x > rd.x || mPos.y > rd.y)))
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


void RoundRectButton::Draw()
{
	const int shadow = 3;
	const int push = 1;
	auto rd = pos_ + size_;
	if (isPush_)
	{

		DrawRoundRect(pos_.x + push, pos_.y + push, rd.x + push, rd.y + push, radius2_.x, radius2_.y, color_, true);
		if (fontHandle_ != -1)
		{
			DrawStringToHandle(pos_.x + sPos_.x + push, pos_.y + sPos_.y + push, _StW(str_).c_str(), ~color_, fontHandle_);
		}
		else 
		{
			DrawString(pos_.x + sPos_.x + push, pos_.y + sPos_.y + push, _StW(str_).c_str(), ~color_);
		}
	}
	else
	{
		DrawRoundRect(pos_.x + shadow, pos_.y + shadow, rd.x + shadow, rd.y + shadow, radius2_.x, radius2_.y, 0x000000, true);
		DrawRoundRect(pos_.x, pos_.y, rd.x, rd.y, radius2_.x, radius2_.y, color_, true);
		if (fontHandle_ != -1)
		{
			DrawStringToHandle(pos_.x + sPos_.x, pos_.y + sPos_.y, _StW(str_).c_str(), ~color_, fontHandle_);
		}
		else {
			DrawString(pos_.x + sPos_.x, pos_.y + sPos_.y, _StW(str_).c_str(), ~color_);

		}
	}


}
