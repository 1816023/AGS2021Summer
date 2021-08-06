#include <DxLib.h>
#include <math.h>
#include "../../Mng/ImageMng.h"
#include "../../StringUtil.h"
#include "../../MouseController.h"
#include "../../Mng/SoundMng.h"
#include "Button.h"


Button::Button() 
{
	isPush_ = false;
	autoFlag_ = false;
	reverseFlag_ = false;
	soundHandle_ = -1;
	fontHandle_ = GetDefaultFontHandle();
	clickType_ = MOUSE_INPUT_LEFT;
	tag_ = -1;
	scale_ = 1.0f;
}

Button::~Button()
{
}

bool Button::Update()
{
	isPush_ = false;
	//lpMouseController.Update();
	if (autoFlag_)
	{
		if (lpMouseController.GetClicking(clickType_))
		{
			SetSound();
			IsHit();
		}
		if (reverseFlag_)
		{
			if (lpMouseController.GetClickUp(clickType_))
			{
				if (IsHit())
				{
					if (soundHandle_ != -1)
					{
						PlaySoundMem(soundHandle_, DX_PLAYTYPE_BACK);
					}
					PushFunction();
					return true;
				}
			}
		}
		else
		{
			if (lpMouseController.GetClickTrg(clickType_))
			{
				if (IsHit())
				{
					if (soundHandle_ != -1)
					{
						PlaySoundMem(soundHandle_, DX_PLAYTYPE_BACK);
					}
					PushFunction();
					return true;
				}
			}

		}
	}
	return false;
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

void Button::SetString(std::string str, VECTOR2 sPos, int fontHandle)
{
	str_ = str;
	sPos_ = sPos;
	fontHandle_ = fontHandle;
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

void Button::SetTag(int tag)
{
	tag_ = tag;
}

void Button::SetSound(int handle)
{
	soundHandle_ = (handle==-2?lpSoundMng.GetID("data/Sound/SE/DefaultButton.mp3"):handle);
}

void Button::SetScale(float scale)
{
	scale_ = scale;
}

void Button::SetFont(int handle)
{
	fontHandle_=handle;
}

