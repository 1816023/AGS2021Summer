#include "MouseController.h"
#include <DxLib.h>
#include "Application.h"

std::unique_ptr<MouseController, MouseController::MouseDelete> MouseController::s_Instans(new MouseController);

bool MouseController::GetClickTrg(int mouseType)
{
	if((data & mouseType) && !(dataOld & mouseType))
	{
		return true;
	}
	return false;
}

bool MouseController::GetClicking(int mouseType)
{
	if((data & mouseType) && (dataOld & mouseType))
	{
		return true;
	}
	return false;
}

bool MouseController::GetClickUp(int mouseType)
{
	if(!(data & mouseType)&&(dataOld & mouseType))
	{		
		return true;
	}
	return false;
}

void MouseController::Update(Vec2Float offset, float scale)
{
	GetMousePoint(&pos.x, &pos.y);
	dataOld = data;
	data = GetMouseInput();
	wheel = GetMouseWheelRotVol();
	offset_ = offset;
	scale_ = scale;
}

const VECTOR2& MouseController::GetOffsetPos()
{
	Vec2Float screenS = { DEF_SCREEN_SIZE_X / 2, DEF_SCREEN_SIZE_Y / 2 };
	auto fPos = VecFCast(pos);
	VECTOR2 set = {};
	// 座標オフセット
	
	if (scale_ != 1.0f)
	{
		// 拡縮のみ
		set = VecICast(screenS / ((1.0f / (scale_ - 1.0f)) + 1.0f));
	}
	set += VecICast(offset_);
	auto a = fPos * (1.0f / scale_);	// 正解
	return VecICast(a + set);
}

const bool MouseController::IsHitBoxToMouse(VECTOR2 lu, VECTOR2 rd)
{
	if (!((pos.x < lu.x || pos.y < lu.y) || (pos.x<lu.x || pos.y>rd.y) || (pos.x > rd.x || pos.y < lu.y) || (pos.x > rd.x || pos.y > rd.y)))
	{
		return true;
	}
	return false;
}

MouseController::MouseController()
{
	data = 0;
	dataOld = 0;
	wheel = 0;
}

MouseController::~MouseController()
{
}
