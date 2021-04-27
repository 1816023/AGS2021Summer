#include <DxLib.h>
#include <list>
#include "TitleScene.h"
#include "../Application.h"
#include "CustomMapScene.h"
#include "../Mng/ImageMng.h"
#include "../MouseController.h"

CustomMapScene::CustomMapScene()
{
	map_ = std::make_unique<Custom>(VECTOR2());
	nowState_ = CustomState::SET_STATE;
	updateFunc_.try_emplace(CustomState::SET_STATE,std::bind(&CustomMapScene::SetStateUpdate,this));
	updateFunc_.try_emplace(CustomState::MAP_CUSTOM,std::bind(&CustomMapScene::Map_CuntomUpdate,this));
	updateFunc_.try_emplace(CustomState::END_CUSTOM,std::bind(&CustomMapScene::EndCustomUpdate,this));

	drawFunc_.try_emplace(CustomState::SET_STATE, std::bind(&CustomMapScene::SetStateDraw, this));
	drawFunc_.try_emplace(CustomState::MAP_CUSTOM, std::bind(&CustomMapScene::MapCustomDraw, this));
	drawFunc_.try_emplace(CustomState::END_CUSTOM, std::bind(&CustomMapScene::EndCustomDraw, this));

	mapSizeX = 0;
	mapSizeY = 0;
	fileName[0] = TCHAR();
	blendAlpha = 256;
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
	//blendAlpha+=2;

	updateFunc_[nowState_]();
	return std::move(own);
}

void CustomMapScene::Draw()
{
	Vec2Float cPos= Application::Instance().GetCamera().GetPos();
	cPos *= 2.0f;
	//DrawString(100, 100, L"CustomMapScene", 0xffffff);
	VECTOR2 mPos = lpMouseController.GetPos();
#ifdef _DEBUG
	DrawFormatString(mPos.x+cPos.x, mPos.y+cPos.y-10, 0xffffff, L"%d", static_cast<int>(map_->GetMapChip(mPos + cPos)));
#endif // DEBUG

	if (nowState_ == CustomState::MAP_CUSTOM)
	{
		map_->Draw();
		
		if (!lpMouseController.IsHitBoxToMouse(SELECT_UI_DRAW.first, SELECT_UI_DRAW.second) && !lpMouseController.IsHitBoxToMouse(TEXT_UI_DRAW.first, TEXT_UI_DRAW.second))
		{
			if (lpMouseController.IsHitBoxToMouse(VECTOR2(0, 0)-cPos, map_->GetMapSize() * map_->GetChipSize() -cPos))
			{
				mPos = (mPos+cPos) / (map_->GetChipSize()) * (map_->GetChipSize());
				SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA,std::abs(128- blendAlpha%256));
				DrawBox(mPos.x, mPos.y, (mPos.x) + map_->GetChipSize().x, (mPos.y) + map_->GetChipSize().y, 0xcccc00, true);
				SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

			}
		}
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
		if (mPos.x > SELECT_UI_DRAW.first.x)
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
	DrawString(0, STRING_HIGHT, L"マップの横幅：", 0xffffff);
	DrawString(0, STRING_HIGHT+LINE_SPACING, L"マップの高さ：", 0xffffff);
	DrawString(0, STRING_HIGHT + LINE_SPACING*2, L"ファイル名：", 0xffffff);
	DrawString(0, STRING_HIGHT*2 + LINE_SPACING*2, L"※次の文字とスペースは使用できません\n「￥　／　：　＊　？　”　＜　＞　｜　.　& ( ) [ ] { } ^ = ; ! ' + , ` ~」", 0xff9999);
	int tmpFlag = 0;
	mapSizeX = KeyInputNumber(GetDrawStringWidth(L"マップの横幅：", GetStringLength(L"マップの横幅：")) + 1, STRING_HIGHT, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	if (mapSizeX<MIN_MAP_SIZE || mapSizeX>MAX_MAP_SIZE)
	{
		return;
	}
	else
	{
		tmpFlag++;
	}
	DrawFormatString(GetDrawStringWidth(L"マップの横幅：", GetStringLength(L"マップの横幅：")) + 1, STRING_HIGHT, 0xffffff, L"%d", mapSizeX);
	mapSizeY = KeyInputNumber(GetDrawStringWidth(L"マップの高さ：", GetStringLength(L"マップの高さ：")) + 1, STRING_HIGHT+LINE_SPACING, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	if (mapSizeY<MIN_MAP_SIZE || mapSizeY>MAX_MAP_SIZE)
	{
		return;
	}
	else
	{
		tmpFlag++;
	}
	DrawFormatString(GetDrawStringWidth(L"マップの高さ：", GetStringLength(L"マップの高さ：")) + 1, STRING_HIGHT + LINE_SPACING, 0xffffff, L"%d", mapSizeY);
	if (KeyInputString(GetDrawStringWidth(L"ファイル名：", GetStringLength(L"ファイル名：")) + 1, STRING_HIGHT+LINE_SPACING*2, MAX_NAME_SIZE, fileName, true) != 1)
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

void CustomMapScene::MapCustomDraw()
{
	DrawString(0, 0, L"Custom", 0xffffff);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawRoundRect(SELECT_UI_DRAW.first.x, SELECT_UI_DRAW.first.y, SELECT_UI_DRAW.second.x, SELECT_UI_DRAW.second.y,20,20, 0x555555, true);
	DrawRoundRect(SELECT_UI_DRAW.first.x, SELECT_UI_DRAW.first.y, SELECT_UI_DRAW.second.x, SELECT_UI_DRAW.second.y, 20, 20, 0xffffff, false);
	DrawRoundRect(TEXT_UI_DRAW.first.x, TEXT_UI_DRAW.first.y, TEXT_UI_DRAW.second.x, TEXT_UI_DRAW.second.y, 20, 20, 0x555555, true);
	DrawRoundRect(TEXT_UI_DRAW.first.x, TEXT_UI_DRAW.first.y, TEXT_UI_DRAW.second.x, TEXT_UI_DRAW.second.y, 20, 20, 0xffffff, false);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

	VECTOR2 mPos = lpMouseController.GetPos();
	if (lpMouseController.GetClicking())
	{
		if (lpMouseController.IsHitBoxToMouse(SELECT_UI_DRAW.first,SELECT_UI_DRAW.second))
		{
			DrawRoundRect(SELECT_UI_DRAW.first.x + 10+1, 10+1, SELECT_UI_DRAW.first.x + 64 + 10+1, 64 + 10+1, 10, 10, 0xffffff, true);
		}
		else
		{
			DrawRoundRect(SELECT_UI_DRAW.first.x + 10 + 3, 10 + 3, SELECT_UI_DRAW.first.x + 64 + 10 + 3, 64 + 10 + 3, 10, 10, 0x000000, true);
			DrawRoundRect(SELECT_UI_DRAW.first.x + 10, 10, SELECT_UI_DRAW.first.x + 64 + 10, 64 + 10, 10, 10, 0xffffff, true);
		}
	}
	else {
		DrawRoundRect(SELECT_UI_DRAW.first.x + 10 + 3, 10 + 3, SELECT_UI_DRAW.first.x + 64 + 10 + 3, 64 + 10 + 3, 10, 10, 0x000000, true);
		DrawRoundRect(SELECT_UI_DRAW.first.x + 10, 10, SELECT_UI_DRAW.first.x + 64 + 10, 64 + 10, 10, 10, 0xffffff, true);
	}
	
#ifdef _DEBUG

	DrawFormatString(mPos.x, mPos.y+10, 0x00ff00, L"%d:%d", mPos.x, mPos.y);
	DrawFormatString(mPos.x, mPos.y + 30, 0x0000ff, L"%d:%d", mPos.x + static_cast<int>(lpApplication.GetCamera().GetPos().x), mPos.y + static_cast<int>(lpApplication.GetCamera().GetPos().y));
#endif // _DEBUG




}

void CustomMapScene::EndCustomDraw()
{
	DrawString(0, 0, L"End", 0xffffff);

}

bool CustomMapScene::FileNameErrorCheck(std::wstring fileName)
{
	//￥　／　：　＊　？　”　＜　＞　｜
	auto check = [](TCHAR code) {
		std::list<TCHAR> wErrorCode = { L'\\',L'/',L':',L'*',L'?',L'<',L'>',L'|',L' ',L'.' };	// Windowsのファイルに使用できないもの
		std::list<TCHAR> cErrorCode = { L'&', L'(',L')', L'[',L']' ,L'{',L'}', L'^', L'=', L';', L'!',L'\'', L'+', L',', L'`', L'~' };	// ついでに念のため省いておく
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
		// Windowsのエラーコードだった場合
		if (check(fileName.c_str()[f]))
		{
			return true;
		}
		// 中身が空だった場合
		if (fileName.c_str()[0] == TCHAR())
		{
			return true;
		}
	}


	return false;
}
