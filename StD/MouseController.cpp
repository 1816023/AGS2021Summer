#include "MouseController.h"
#include <DxLib.h>
#include "Application.h"

std::unique_ptr<MouseController, MouseController::MouseDelete> MouseController::s_Instans(new MouseController);

bool MouseController::GetClickTrg(int mouseType)
{
	if (data && !dataOld && (data & mouseType))
	{
		return true;
	}
	return false;
}

bool MouseController::GetClicking(int mouseType)
{
	if (data && dataOld && (data & mouseType))
	{
		return true;
	}
	return false;
}

bool MouseController::GetClickUp(int mouseType)
{
	if (!data && dataOld && (dataOld & mouseType))
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
	wheel += GetMouseWheelRotVol();
	offset_ = offset;
	scale_ = scale;
}

const VECTOR2& MouseController::GetOffsetPos()
{
	Vec2Float screenS = { DEF_SCREEN_SIZE_X, DEF_SCREEN_SIZE_Y };
	auto set = VecICast(screenS * (1.0f / (1.0f + scale_)));
	return pos + VecICast(offset_);
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
