#include <DxLib.h>
#include <math.h>
#include "Mng/ImageMng.h"
#include "Button.h"

Button::Button(VECTOR2 lu, VECTOR2 rd, int color, std::function<bool()> func, VECTOR2 offset):lu_(lu),rd_(rd),color_(color),func_(func),offset_(offset)
{
	type_ = ButtonType::Box;
	isHitFunc_ = std::bind(&Button::BoxHit,this,std::placeholders::_1);
	drawFunc_ = std::bind(&Button::BoxDraw, this);
	isPush_ = false;
	isClick_ = false;
}

Button::Button(VECTOR2 pos, int radius, int color, std::function<bool()> func, VECTOR2 offset)
	:pos_(pos),radius_(radius),color_(color),func_(func), offset_(offset)
{
	type_ = ButtonType::Circle;
	isHitFunc_ = std::bind(&Button::CircleHit, this, std::placeholders::_1);
	drawFunc_ = std::bind(&Button::CircleDraw, this);
	isPush_ = false;
	isClick_ = false;
}

Button::Button(VECTOR2 lu, VECTOR2 rd, VECTOR2 radius, int color, std::function<bool()> func, VECTOR2 offset)
	:lu_(lu),rd_(rd),radius2_(radius),color_(color),func_(func), offset_(offset)
{
	type_ = ButtonType::RoundRect;
	isHitFunc_ = std::bind(&Button::RoundRectHit, this, std::placeholders::_1);
	drawFunc_ = std::bind(&Button::RoundRect, this);
	isPush_ = false;
	isClick_ = false;

}

Button::Button(VECTOR2 pos, VECTOR2 size, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()> func, VECTOR2 offset)
	:pos_(pos),size_(size),imagePath_(imagePath),pushImagePath_(pushImagePath),func_(func), offset_(offset)
{
	type_ = ButtonType::BoxImage;	
	isHitFunc_ = std::bind(&Button::BoxImageHit, this, std::placeholders::_1);
	drawFunc_ = std::bind(&Button::BoximageDraw, this);
	isPush_ = false;
	isClick_ = false;
}

Button::Button(VECTOR2 pos, int radius, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()> func, VECTOR2 offset)
	:pos_(pos),radius_(radius),imagePath_(imagePath),pushImagePath_(pushImagePath),func_(func), offset_(offset)
{
	type_ = ButtonType::CircleImage;
	isHitFunc_ = std::bind(&Button::CircleImageHit, this, std::placeholders::_1);
	drawFunc_ = std::bind(&Button::CircleImageDraw, this);
	isPush_ = false;
	isClick_ = false;
}

Button::~Button()
{
}

bool Button::IsHit(VECTOR2 mPos)
{
	return isHitFunc_(mPos);
}

bool Button::IsHit()
{
	VECTOR2 mPos;
	GetMousePoint(&mPos.x, &mPos.y);
	return isHitFunc_(mPos);
}

void Button::Draw()
{
	drawFunc_();
}

bool Button::BoxHit(VECTOR2 mPos)
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

bool Button::CircleHit(VECTOR2 mPos)
{
	auto tmp = pos_ - mPos;
	auto r = std::sqrt((tmp.x*tmp.x)+(tmp.y*tmp.y));
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

bool Button::RoundRectHit(VECTOR2 mPos)
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

bool Button::BoxImageHit(VECTOR2 mPos)
{
	if (!((mPos.x < pos_.x || mPos.y < pos_.y) || (mPos.x<pos_.x || mPos.y>pos_.y+size_.y) || (mPos.x > pos_.x+size_.x || mPos.y < pos_.y) || (mPos.x > pos_.x +size_.x|| mPos.y > pos_.y+size_.y)))
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

bool Button::CircleImageHit(VECTOR2 mPos)
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

void Button::BoxDraw()
{

	const int shadow = 3;
	const int push = 1;
	if (isPush_)
	{
		DrawBox(lu_.x + offset_.x + push, lu_.y + offset_.y + push, rd_.x + offset_.x + push, rd_.y + offset_.y + push, color_, true);

	}
	else
	{
		DrawBox(lu_.x + offset_.x + shadow, lu_.y + offset_.y + shadow, rd_.x + offset_.x + shadow, rd_.y + offset_.y + shadow, 0x000000, true);
		DrawBox(lu_.x, lu_.y, rd_.x, rd_.y, color_, true);

	}


}

void Button::CircleDraw()
{
	const int shadow = 3;
	const int push = 1;
	if (isPush_)
	{
		DrawCircle(pos_.x + offset_.x + push, pos_.y + offset_.y + push, radius_, color_, true);

	}
	else
	{
		DrawCircle(pos_.x + offset_.x + shadow, pos_.y + offset_.y + shadow,radius_, 0x000000, true);
		DrawCircle(pos_.x, pos_.y, radius_, color_, true);

	}
}

void Button::RoundRect()
{
	const int shadow = 3;
	const int push=1;
	if (isPush_)
	{
		DrawRoundRect(lu_.x + offset_.x+push, lu_.y + offset_.y+push, rd_.x + offset_.x+push, rd_.y + offset_.y+push, radius2_.x, radius2_.y, color_, true);

	}
	else
	{
		DrawRoundRect(lu_.x + offset_.x+shadow, lu_.y + offset_.y+shadow, rd_.x + offset_.x+shadow, rd_.y + offset_.y+shadow, radius2_.x, radius2_.y, 0x000000, true);
		DrawRoundRect(lu_.x, lu_.y, rd_.x, rd_.y, radius2_.x, radius2_.y, color_, true);

	}

}

void Button::BoximageDraw()
{
	if (isPush_)
	{
		DrawGraph(pos_.x + offset_.x, pos_.x + offset_.y, IMAGE_ID(pushImagePath_.c_str()), true);
	}
	else
	{
		DrawGraph(pos_.x + offset_.x, pos_.x + offset_.y, IMAGE_ID(imagePath_.c_str()), true);
	}
}

void Button::CircleImageDraw()
{
	if (isPush_)
	{
		DrawGraph(pos_.x + offset_.x, pos_.x + offset_.y, IMAGE_ID(pushImagePath_.c_str()), true);
	}
	else
	{
		DrawGraph(pos_.x + offset_.x, pos_.x + offset_.y, IMAGE_ID(imagePath_.c_str()), true);
	}
}

