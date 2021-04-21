#include <DxLib.h>
#include <list>
#include "TitleScene.h"
#include "../Application.h"
#include "CustomMapScene.h"

CustomMapScene::CustomMapScene()
{
	map_ = std::make_unique<Custom>(VECTOR2());
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
	//DrawString(100, 100, L"CustomMapScene", 0xffffff);
	if (nowState_ == CustomState::MAP_CUSTOM)
	{
		map_->Draw();
	}

}

void CustomMapScene::DrawUI()
{
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
	VECTOR2 mPos;
	GetMousePoint(&mPos.x, &mPos.y);
	if (GetMouseInput() & MOUSE_INPUT_LEFT == 1)
	{
		if (mPos.x > MAX_MAP_DRAW.x)
		{

		}
		else
		{
			map_->SetChip(mPos, MapChipName::ROOT);
		}
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
	DrawString(0, STRING_HIGHT, L"�}�b�v�̉����F", 0xffffff);
	DrawString(0, STRING_HIGHT+LINE_SPACING, L"�}�b�v�̍����F", 0xffffff);
	DrawString(0, STRING_HIGHT + LINE_SPACING*2, L"�t�@�C�����F", 0xffffff);
	DrawString(0, STRING_HIGHT*2 + LINE_SPACING*2, L"�����̕����ƃX�y�[�X�͎g�p�ł��܂���\n�u���@�^�@�F�@���@�H�@�h�@���@���@�b�@.�@& ( ) [ ] { } ^ = ; ! ' + , ` ~�v", 0xff9999);
	int tmpFlag = 0;
	mapSizeX = KeyInputNumber(GetDrawStringWidth(L"�}�b�v�̉����F", GetStringLength(L"�}�b�v�̉����F")) + 1, STRING_HIGHT, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	if (mapSizeX<MIN_MAP_SIZE || mapSizeX>MAX_MAP_SIZE)
	{
		return;
	}
	else
	{
		tmpFlag++;
	}
	DrawFormatString(GetDrawStringWidth(L"�}�b�v�̉����F", GetStringLength(L"�}�b�v�̉����F")) + 1, STRING_HIGHT, 0xffffff, L"%d", mapSizeX);
	mapSizeY = KeyInputNumber(GetDrawStringWidth(L"�}�b�v�̍����F", GetStringLength(L"�}�b�v�̍����F")) + 1, STRING_HIGHT+LINE_SPACING, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	if (mapSizeY<MIN_MAP_SIZE || mapSizeY>MAX_MAP_SIZE)
	{
		return;
	}
	else
	{
		tmpFlag++;
	}
	DrawFormatString(GetDrawStringWidth(L"�}�b�v�̍����F", GetStringLength(L"�}�b�v�̍����F")) + 1, STRING_HIGHT + LINE_SPACING, 0xffffff, L"%d", mapSizeY);
	if (KeyInputString(GetDrawStringWidth(L"�t�@�C�����F", GetStringLength(L"�t�@�C�����F")) + 1, STRING_HIGHT+LINE_SPACING*2, MAX_NAME_SIZE, fileName, true) != 1)
	{
		return;
	}
	else {
		if (FileNameErrorCheck(fileName))
		{
			return;
		}
		tmpFlag++;
	}
	if (tmpFlag >= 3)
	{
		nowState_= CustomState::MAP_CUSTOM;
		dynamic_cast<Custom*>(map_.get())->SetUp(fileName, VECTOR2(mapSizeX, mapSizeY));
	}
}

void CustomMapScene::MapCuntomDraw()
{
	DrawString(0, 0, L"Custom", 0xffffff);
	DrawBox(MAX_MAP_DRAW.x, 0, DEF_SCREEN_SIZE_X, DEF_SCREEN_SIZE_Y, 0x555555, true);
	DrawLine(MAX_MAP_DRAW.x, 0, MAX_MAP_DRAW.x, MAX_MAP_DRAW.y, 0xffffff);
}

void CustomMapScene::EndCustomDraw()
{
	DrawString(0, 0, L"End", 0xffffff);

}

bool CustomMapScene::FileNameErrorCheck(std::wstring fileName)
{
	//���@�^�@�F�@���@�H�@�h�@���@���@�b
	auto check = [](TCHAR code) {
		std::list<TCHAR> wErrorCode = { L'\\',L'/',L':',L'*',L'?',L'<',L'>',L'|',L' ',L'.' };	// Windows�̃t�@�C���Ɏg�p�ł��Ȃ�����
		std::list<TCHAR> cErrorCode = { L'&', L'(',L')', L'[',L']' ,L'{',L'}', L'^', L'=', L';', L'!',L'\'', L'+', L',', L'`', L'~' };	// ���łɔO�̂��ߏȂ��Ă���
		for (auto error : wErrorCode)
		{
			if (code == error)
			{
				return true;
			}
		}
		for (auto error : cErrorCode)
		{
			if (code == error)
			{
				return true;
			}
		}
		return false;
	};

	for (int f = 0; f < MAX_NAME_SIZE; f++)
	{
		// Windows�̃G���[�R�[�h�������ꍇ
		if (check(fileName.c_str()[f]))
		{
			return true;
		}
		// ���g���󂾂����ꍇ
		if (fileName.c_str()[0] == TCHAR())
		{
			return true;
		}
	}


	return false;
}
