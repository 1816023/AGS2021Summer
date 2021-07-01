#include <DxLib.h>
#include "../Mng/ImageMng.h"
#include "../StringUtil.h"
#include "RoundRectButton.h"

RoundRectButton::RoundRectButton(VECTOR2 lu, VECTOR2 rd, VECTOR2 radius, int color, std::function<bool()> func, VECTOR2 offset)
	:Button(offset)
{
	lu_ = lu;
	rd_ = rd;
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


void RoundRectButton::Draw()
{
	const int shadow = 3;
	const int push = 1;
	if (isPush_)
	{
		DrawRoundRect(lu_.x + offset_.x + push, lu_.y + offset_.y + push, rd_.x + offset_.x + push, rd_.y + offset_.y + push, radius2_.x, radius2_.y, color_, true);
		if (fontHandle_ != -1)
		{
			DrawStringToHandle(lu_.x + sPos_.x + push+ offset_.x, lu_.y + sPos_.y + push+ offset_.y, _StW(str_).c_str(), ~color_, fontHandle_);
		}
		else 
		{
			DrawString(lu_.x + sPos_.x + push+offset_.x, lu_.y + sPos_.y + push+offset_.y, _StW(str_).c_str(), ~color_);
		}
	}
	else
	{
		DrawRoundRect(lu_.x + offset_.x + shadow, lu_.y + offset_.y + shadow, rd_.x + offset_.x + shadow, rd_.y + offset_.y + shadow, radius2_.x, radius2_.y, 0x000000, true);
		DrawRoundRect(lu_.x + offset_.x, lu_.y + offset_.y, rd_.x + offset_.x, rd_.y + offset_.y, radius2_.x, radius2_.y, color_, true);
		if (fontHandle_ != -1)
		{
			DrawStringToHandle(lu_.x + sPos_.x  + offset_.x, lu_.y + sPos_.y  + offset_.y, _StW(str_).c_str(), ~color_, fontHandle_);
		}
		else {
			DrawString(lu_.x + sPos_.x  + offset_.x, lu_.y + sPos_.y  + offset_.y, _StW(str_).c_str(), ~color_);

		}
	}


}
