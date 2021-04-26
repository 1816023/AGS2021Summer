#include "MouseController.h"
#include <DxLib.h>

std::unique_ptr<MouseController, MouseController::MouseDelete> MouseController::s_Instans(new MouseController);

bool MouseController::GetClickTrg()
{
	if (data && !dataOld)
	{
		return true;
	}
	return false;
}

bool MouseController::GetClicking()
{
	if (data && dataOld)
	{
		return true;
	}
	return false;
}

void MouseController::Update()
{
	GetMousePoint(&pos.x, &pos.y);
	dataOld = data;
	data = GetMouseInput();
	wheel += GetMouseWheelRotVol();
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
