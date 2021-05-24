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

void RectButton::Update()
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
		DrawBox(lu_.x + offset_.x + push, lu_.y + offset_.y + push, rd_.x + offset_.x + push, rd_.y + offset_.y + push, color_, true);
		DrawString(lu_.x, lu_.y, _StW(str_).c_str(), ~color_);
	}
	else
	{
		DrawBox(lu_.x + offset_.x + shadow, lu_.y + offset_.y + shadow, rd_.x + offset_.x + shadow, rd_.y + offset_.y + shadow, 0x000000, true);
		DrawBox(lu_.x, lu_.y, rd_.x, rd_.y, color_, true);
		DrawString(lu_.x, lu_.y, _StW(str_).c_str(), ~color_);

	}

}
