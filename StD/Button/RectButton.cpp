#include <DxLib.h>
#include "../Mng/ImageMng.h"
#include "../StringUtil.h"
#include "RectButton.h"

RectButton::RectButton(VECTOR2 lu, VECTOR2 rd, int color, std::function<bool()> func, VECTOR2 offset)
	: Button(offset)
{
	lu_ = lu;
	rd_ = rd;
	color_ = color;
	func_ = func;
	type_ = ButtonType::Rect;

}

RectButton::~RectButton()
{
}


bool RectButton::IsHit(VECTOR2 mPos)
{
	auto lu = lu_ + offset_;
	auto rd = rd_ + offset_;
	if (!((mPos.x < lu.x || mPos.y < lu.y) || (mPos.x<lu.x || mPos.y>rd.y) || (mPos.x > rd.x || mPos.y < lu.y) || (mPos.x > rd.x || mPos.y > rd.y)))
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
		DrawBox(lu_.x + offset_.x + push, lu_.y + offset_.y + push, rd_.x + offset_.x + push, rd_.y + offset_.y + push, color_, true);
		DrawString(lu_.x+offset_.x+ push+sPos_.x, lu_.y+offset_.y+ push+sPos_.y, _StW(str_).c_str(), ~color_);
	}
	else
	{
		DrawBox(lu_.x + offset_.x + shadow, lu_.y + offset_.y + shadow, rd_.x + offset_.x + shadow, rd_.y + offset_.y + shadow, 0x000000, true);
		DrawBox(lu_.x+offset_.x, lu_.y+offset_.y, rd_.x+offset_.x, rd_.y+offset_.y, color_, true);
		DrawString(lu_.x+offset_.x+sPos_.x, lu_.y+offset_.y+sPos_.y, _StW(str_).c_str(), ~color_);

	}

}
