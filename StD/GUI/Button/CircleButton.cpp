#include <DxLib.h>
#include "../../Mng/ImageMng.h"
#include "../../StringUtil.h"
#include "CircleButton.h"

CircleButton::CircleButton(VECTOR2 pos, int radius, int color, std::function<bool()> func)
{
	pos_ = pos;
	radius_ = radius;
	color_ = color;
	func_ = func;
	type_ = ButtonType::Circle;

}

CircleButton::CircleButton(int radius, int color, std::function<bool()> func)
{
	radius_ = radius;
	color_ = color;
	func_ = func;
	type_ = ButtonType::Circle;
}

CircleButton::~CircleButton()
{
}

bool CircleButton::IsHit(VECTOR2 mPos)
{
	auto tmp = pos_ - mPos;
	auto r = std::sqrt((tmp.x * tmp.x) + (tmp.y * tmp.y));
	if (r <= radius_)
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


void CircleButton::Draw()
{
	const int shadow = 3;
	const int push = 1;
	if (isPush_)
	{
		DrawCircle(pos_.x + push, pos_.y + push, radius_, color_, true);
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
		DrawCircle(pos_.x + shadow, pos_.y + shadow, radius_, 0x000000, true);
		DrawCircle(pos_.x, pos_.y, radius_, color_, true);
		if (fontHandle_ != -1)
		{
			DrawStringToHandle(lu_.x + sPos_.x , lu_.y + sPos_.y, _StW(str_).c_str(), ~color_, fontHandle_);
		}
		else {
			DrawString(lu_.x + sPos_.x , lu_.y + sPos_.y, _StW(str_).c_str(), ~color_);

		}
	}

}
