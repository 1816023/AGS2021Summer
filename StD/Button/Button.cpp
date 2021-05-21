#include <DxLib.h>
#include <math.h>
#include "../Mng/ImageMng.h"
#include "../StringUtil.h"
#include "Button.h"


Button::Button(VECTOR2 offset) :offset_(offset)
{
	isPush_ = false;
	isClick_ = false;

}

Button::~Button()
{
}

void Button::Update()
{
	isPush_ = false;
}

bool Button::IsHit()
{
	VECTOR2 mPos;
	GetMousePoint(&mPos.x, &mPos.y);
	return IsHit(mPos);
}

void Button::Draw()
{
	drawFunc_();
}

void Button::SetZbuff(int z)
{
	zBuff_ = z;
}

void Button::SetString(std::string str, VECTOR2 sPos)
{
	str_ = str;
	sPos_ = sPos;
}

