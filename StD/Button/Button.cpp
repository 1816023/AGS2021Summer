#include <DxLib.h>
#include <math.h>
#include "../Mng/ImageMng.h"
#include "../StringUtil.h"
#include "../MouseController.h"
#include "Button.h"


Button::Button(VECTOR2 offset) :offset_(offset)
{
	isPush_ = false;
	isClick_ = false;
	autoFlag_ = false;
	reverseFlag_ = false;
	clickType_ = MOUSE_INPUT_LEFT;
}

Button::~Button()
{
}

void Button::Update()
{
	isPush_ = false;
	//lpMouseController.Update();
	if (autoFlag_)
	{
		if (lpMouseController.GetClicking(clickType_))
		{
			IsHit();
		}
		if (reverseFlag_)
		{
			if (lpMouseController.GetClickUp(clickType_))
			{
				PushFunction();
			}
		}
		else
		{
			if (lpMouseController.GetClickTrg(clickType_))
			{
				if (IsHit())
				{
					PushFunction();
				}
			}

		}
	}

}

const bool Button::IsHit()
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

void Button::SetAuto()
{
	autoFlag_ = true;
}

void Button::SetReversePush()
{
	reverseFlag_ = true;
}

void Button::SetClickType(int type)
{
	clickType_ = type;
}

