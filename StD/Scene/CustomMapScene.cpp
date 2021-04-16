#include <DxLib.h>
#include "TitleScene.h"
#include "CustomMapScene.h"

CustomMapScene::CustomMapScene()
{
	map_ = std::make_unique<Custom>();
	nowState_ = CustomState::SET_STATE;
	updateFunc_.try_emplace(CustomState::SET_STATE,std::bind(&CustomMapScene::SetStateUpdate,this));
	updateFunc_.try_emplace(CustomState::MAP_CUSTOM,std::bind(&CustomMapScene::Map_CuntomUpdate,this));
	updateFunc_.try_emplace(CustomState::END_CUSTOM,std::bind(&CustomMapScene::EndCustomUpdate,this));

	drawFunc_.try_emplace(CustomState::SET_STATE, std::bind(&CustomMapScene::SetStateDraw, this));
	drawFunc_.try_emplace(CustomState::MAP_CUSTOM, std::bind(&CustomMapScene::MapCuntomDraw, this));
	drawFunc_.try_emplace(CustomState::END_CUSTOM, std::bind(&CustomMapScene::EndCustomDraw, this));

	mapSizeX = 0;
	mapSizeY = 0;
	fileName[0] = TCHAR();
}

CustomMapScene::~CustomMapScene()
{
}

unique_Base CustomMapScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);

	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE]))
	{
		return std::make_unique<TitleScene>();
	}

	updateFunc_[nowState_]();
	return std::move(own);
}

void CustomMapScene::Draw()
{
	DrawString(100, 100, L"CustomMapScene", 0xffffff);
	drawFunc_[nowState_]();
}

void CustomMapScene::SetStateUpdate()
{
	if ((now[KEY_INPUT_BACK]) & (~old[KEY_INPUT_BACK]))
	{
		//nowState_ = CustomState::MAP_CUSTOM;
	}
}

void CustomMapScene::Map_CuntomUpdate()
{
	if ((now[KEY_INPUT_BACK]) & (~old[KEY_INPUT_BACK]))
	{
		nowState_ = CustomState::END_CUSTOM;
	}
}

void CustomMapScene::EndCustomUpdate()
{
	if ((now[KEY_INPUT_BACK]) & (~old[KEY_INPUT_BACK]))
	{
		nowState_ = CustomState::SET_STATE;
	}
}

void CustomMapScene::SetStateDraw()
{
	DrawString(0, 0, L"Set", 0xffffff);
	DrawString(0, 20, L"マップの横幅：", 0xffffff);
	DrawString(0, 50, L"マップの高さ：", 0xffffff);
	DrawString(0, 80, L"ファイル名：", 0xffffff);
	mapSizeX = KeyInputNumber(GetDrawStringWidth(L"マップの横幅：", GetStringLength(L"マップの横幅：")) + 1, 20, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	if (mapSizeX<MIN_MAP_SIZE || mapSizeX>MAX_MAP_SIZE)
	{
		return;
	}
	DrawFormatString(GetDrawStringWidth(L"マップの横幅：", GetStringLength(L"マップの横幅：")) + 1, 20, 0xffffff, L"%d", mapSizeX);
	mapSizeY = KeyInputNumber(GetDrawStringWidth(L"マップの高さ：", GetStringLength(L"マップの高さ：")) + 1, 50, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	if (mapSizeY<MIN_MAP_SIZE || mapSizeY>MAX_MAP_SIZE)
	{
		return;
	}
	DrawFormatString(GetDrawStringWidth(L"マップの高さ：", GetStringLength(L"マップの高さ：")) + 1, 50, 0xffffff, L"%d", mapSizeY);
	if (KeyInputString(GetDrawStringWidth(L"ファイル名：", GetStringLength(L"ファイル名：")) + 1, 80, 20, fileName, true) != 1)
	{
		return;
	}

}

void CustomMapScene::MapCuntomDraw()
{
	DrawString(0, 0, L"Custom", 0xffffff);

}

void CustomMapScene::EndCustomDraw()
{
	DrawString(0, 0, L"End", 0xffffff);

}
