#include "KeyController.h"
#include <DxLib.h>

std::unique_ptr<KeyController, KeyController::KeyDelete> KeyController::s_Instans(new KeyController);

const keyArray& KeyController::GetCtl(KEY_TYPE type) const
{
	if (type == KEY_TYPE::OLD)
	{
		return dataOld;
	}
	return data;
}

bool KeyController::Update()
{
	dataOld = data;
	GetHitKeyStateAll(&data[0]);
	return true;
}

KeyController::KeyController()
{
}

KeyController::~KeyController()
{
}
