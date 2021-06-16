#include <DxLib.h>
#include <list>
#include "TitleScene.h"
#include "../Application.h"
#include "CustomMapScene.h"
#include "../Mng/ImageMng.h"
#include "../MouseController.h"
#include "../CustomState/SelectFile.h"
#include "../CustomState/SetState.h"
#include "../CustomState/MapCustom.h"
#include "../CustomState/EnemyCustom.h"
#include "../CustomState/EndCustom.h"
#include "../StringUtil.h"
#include "../Map/Astar.h"

#define CUSTOM dynamic_cast<Custom*>(cusMap_.get())
CustomMapScene::CustomMapScene()
{
	Init();
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

	custom_[nowState_]->Update(this);
	return std::move(own);
}

bool CustomMapScene::Init()
{

	cusMap_ = std::make_unique<Custom>(VECTOR2());
	nowState_ = CustomState::SELECT_FILE;
	custom_.try_emplace(CustomState::SELECT_FILE, std::make_unique<SelectFile>());
	custom_.try_emplace(CustomState::SET_STATE, std::make_unique<SetState>());
	custom_.try_emplace(CustomState::MAP_CUSTOM, std::make_unique<MapCustom>());
	custom_.try_emplace(CustomState::ENEMY_CUSTOM, std::make_unique<EnemyCustom>());
	custom_.try_emplace(CustomState::END_CUSTOM, std::make_unique<EndCustom>());
	custom_[nowState_]->Init(this);
	//// update系関数保存
	//updateFunc_.try_emplace(CustomState::SET_STATE, std::bind(&SetState::Update,this));
	//updateFunc_.try_emplace(CustomState::MAP_CUSTOM, std::bind(&MapCustom::Update,this));
	//updateFunc_.try_emplace(CustomState::ENEMY_CUSTOM, std::bind(&EnemyCustom::Update,this));
	//updateFunc_.try_emplace(CustomState::END_CUSTOM, std::bind(&EndCustom::Update,this));
	//// draw系関数保存
	//drawFunc_.try_emplace(CustomState::SET_STATE, std::bind(&SetState::Draw, this));
	//drawFunc_.try_emplace(CustomState::MAP_CUSTOM, std::bind(&MapCustom::Draw, this));
	//drawFunc_.try_emplace(CustomState::ENEMY_CUSTOM, std::bind(&EnemyCustom::Draw, this));
	//drawFunc_.try_emplace(CustomState::END_CUSTOM, std::bind(&EndCustom::Draw, this));
	//// init系関数保存
	//initFunc_.try_emplace(CustomState::SET_STATE, std::bind(&SetState::Init, this));
	//initFunc_.try_emplace(CustomState::MAP_CUSTOM, std::bind(&MapCustom::Init, this));
	//initFunc_.try_emplace(CustomState::ENEMY_CUSTOM, std::bind(&EnemyCustom::Init, this));
	//initFunc_.try_emplace(CustomState::END_CUSTOM, std::bind(&EndCustom::Init, this));
	//initFunc_[nowState_](this);
	//const int bSize = 64;
	//const int bSpace = 20;
	//const int basePosX = SELECT_UI_POS.first.x + bSpace;
	//const int basePosY = SELECT_UI_POS.first.x + bSize + bSpace;
	//auto nFunc = [&](ButtomState& state) {
	//	if (state.pushFlag = !state.pushFlag)
	//	{
	//		selChip_ = static_cast<MapChipName>(std::atoi(_WtS(state.name).c_str()));
	//	}
	//	else
	//	{
	//		selChip_ = MapChipName::MAX;
	//	} 
	//};
	//auto sFunc = [&](ButtomState& state) {state.pushFlag = true; CUSTOM->SaveFile(); };
	//bList_.push_back({ VECTOR2(basePosX,bSpace),VECTOR2(basePosY, bSize + bSpace),false,L"1" ,0x007fff,nFunc });
	//bList_.push_back({ VECTOR2(basePosX + (bSize + bSpace),bSpace),VECTOR2(basePosY + (bSize + bSpace), bSize + bSpace),false,L"2",0xff0f0f,nFunc });
	//bList_.push_back({ VECTOR2(basePosX + (bSize + bSpace) * 2,bSpace),VECTOR2(basePosY + (bSize + bSpace) * 2, bSize + bSpace),false,L"3" ,0xafff00, nFunc });
	//bList_.push_back({ VECTOR2(basePosX,bSpace + (bSize + bSpace)),VECTOR2(basePosY, bSize + bSpace + (bSize + bSpace)),false,L"4" ,0xe3e3e3, nFunc });
	//bList_.push_back({ VECTOR2(basePosX + (bSize + bSpace),bSpace + (bSize + bSpace)),VECTOR2(basePosY + (bSize + bSpace), bSize + bSpace + (bSize + bSpace)),false,L"5",0x333333,nFunc });
	//bList_.push_back({ VECTOR2(basePosX + (bSize + bSpace) * 2,bSpace + (bSize + bSpace)),VECTOR2(basePosY + (bSize + bSpace) * 2, bSize + bSpace + (bSize + bSpace)),false,L"save" ,0xffffff, sFunc});
	

	/*button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, bSpace*2), VECTOR2(basePosY, bSize + bSpace*2), VECTOR2(10, 10), 0x007fff, [&]() {selChip_ = MapChipName::MAINSTAY; return false; }, VECTOR2()));
	buttonText_.emplace_back(ButtonText{ "自拠点",0xffffff,VECTOR2(basePosX,  bSpace*2-GetFontSize()) });
	button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace), bSpace*2), VECTOR2(basePosY + (bSize + bSpace), bSize + bSpace * 2),VECTOR2(10,10), 0xff0f0f, [&]() {selChip_ = MapChipName::SPAWNER; return false; }, VECTOR2()));
	buttonText_.emplace_back(ButtonText{ "敵出現", 0xffffff, VECTOR2(basePosX + (bSize + bSpace), bSpace * 2-GetFontSize()) });
	button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace) * 2, bSpace * 2), VECTOR2(basePosY + (bSize + bSpace) * 2, bSize + bSpace * 2),VECTOR2(10,10), 0xfff00, [&]() {selChip_ = MapChipName::ROOT; return false; }, VECTOR2()));
	buttonText_.emplace_back(ButtonText{ "敵侵攻",0xffffff,VECTOR2(basePosX + (bSize + bSpace) * 2, bSpace * 2- GetFontSize() ) });
	button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, bSpace + (bSize + bSpace * 2)), VECTOR2(basePosY, bSize + bSpace + (bSize + bSpace * 2)), VECTOR2(10,10),0xe3e3e3, [&]() {selChip_ = MapChipName::FIELD; return false; }, VECTOR2()));
	buttonText_.emplace_back(ButtonText{ "自機配置",0xffffff,VECTOR2(basePosX, bSpace + (bSize + bSpace * 2) - GetFontSize()) });
	button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace ), bSpace + (bSize + bSpace * 2)), VECTOR2(basePosY + (bSize + bSpace), bSize + bSpace + (bSize + bSpace * 2)),VECTOR2(10,10), 0x333333, [&]() {selChip_ = MapChipName::WALL; return false; }, VECTOR2()));
	buttonText_.emplace_back(ButtonText{ "設置不可",0xffffff,VECTOR2(basePosX + (bSize + bSpace), bSpace + (bSize + bSpace * 2) - GetFontSize()) });
	button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace ) * 2, bSpace + (bSize + bSpace * 2)), VECTOR2(basePosY + (bSize + bSpace) * 2, bSize + bSpace + (bSize + bSpace * 2)),VECTOR2(10,10), 0xffffff, [&]() {selChip_ = MapChipName::MAX; return false; }, VECTOR2()));
	buttonText_.emplace_back(ButtonText{ "選択解除",0xffffff,VECTOR2(basePosX + (bSize + bSpace) * 2, bSpace + (bSize + bSpace * 2) - GetFontSize()) });
	button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, bSize * 2 + bSpace * 4), VECTOR2(basePosY, bSize * 3 + bSpace * 4), VECTOR2(10, 10), 0xffffff, 
		[&]() 
		{
			const auto& spawners = cusMap_->Getspawner();
			const auto& mainStay = cusMap_->GetMainStay();
			if (mainStay != VECTOR2(-1, -1) && spawners.size() != 0)
			{
				astar_->AstarStart(mainStay, spawners.at(0));
			}
			return false; 
		}, VECTOR2()));
	buttonText_.emplace_back(ButtonText{ "ルート作成",0xffffff,VECTOR2(basePosX, bSize * 2 + bSpace * 4 - GetFontSize()) });
	for (auto&& b : button_)
	{
		b->SetAuto();
	}*/

	//mapSizeX_ = 0;
	//mapSizeY_ = 0;
	//fileName_[0] = TCHAR();
	//blendAlpha_ = 256;
	//selChip_ = MapChipName::MAX;
	//LoadText();
	return true;
}

void CustomMapScene::Draw()
{
	Vec2Float cPos= Application::Instance().GetCamera().GetPos();
	cPos *= 2.0f;
	//DrawString(100, 100, L"CustomMapScene", 0xffffff);
	VECTOR2 mPos = lpMouseController.GetPos();

	if (nowState_ == CustomState::MAP_CUSTOM)
	{
#ifdef _DEBUG
	DrawFormatString(mPos.x+cPos.x, mPos.y+cPos.y-10, 0xffffff, L"%d", static_cast<int>(cusMap_->GetMapChip((mPos + cPos))));

#endif // DEBUG

		cusMap_->Draw();
		
		if (!lpMouseController.IsHitBoxToMouse(SELECT_UI_POS.first, SELECT_UI_POS.second) && !lpMouseController.IsHitBoxToMouse(TEXT_UI_POS.first, TEXT_UI_POS.second))
		{
			if (lpMouseController.IsHitBoxToMouse(VecICast((VECTOR2(0, 0)) - cPos), VecICast(cusMap_->GetMapSize() - cPos  * cusMap_->GetChipSize())))
			{
				mPos = VecICast(mPos+cPos) / (cusMap_->GetChipSize()) * (cusMap_->GetChipSize());
				SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA,std::abs(128- blendAlpha_%256));
				DrawBox(mPos.x, mPos.y, (mPos.x) + cusMap_->GetChipSize().x, (mPos.y) + cusMap_->GetChipSize().y, 0xcccc00, true);
				SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

			}
		}
	}
}

void CustomMapScene::DrawUI()
{
	custom_[nowState_]->Draw(this);
	const auto& mainStay = cusMap_->GetMainStay();
	DrawFormatString(0, 48, 0xffffff, L"mainStay x %d, y %d", mainStay.x, mainStay.y);
}

void CustomMapScene::SetStateUpdate()
{
	if ((now[KEY_INPUT_BACK]) & (~old[KEY_INPUT_BACK]))
	{
		//nowState_ = CustomState::MAP_CUSTOM;
	}
}

void CustomMapScene::MapCuntomUpdate()
{
	for (auto&& list : button_)
	{
		list->Update();
	}
	if ((now[KEY_INPUT_BACK]) & (~old[KEY_INPUT_BACK]))
	{
		nowState_ = CustomState::END_CUSTOM;
	}
	VECTOR2 mPos;
	GetMousePoint(&mPos.x, &mPos.y);
	auto cPos = lpApplication.GetCamera().GetPos()*2.0f;
	if (lpMouseController.GetClicking(MOUSE_INPUT_LEFT))
	{
		if (mPos.x > SELECT_UI_POS.first.x)
		{
		}
		else
		{
			cusMap_->SetChip(VecICast(cPos + mPos), selChip_);
		}
	}

	//blendAlpha_+=2;

}

void CustomMapScene::EndCustomUpdate()
{
	//if ((now[KEY_INPUT_BACK]) & (~old[KEY_INPUT_BACK]))
	//{
	//	nowState_ = CustomState::SET_STATE;
	//}
	//if ((now[KEY_INPUT_RETURN]) & (~old[KEY_INPUT_RETURN]))
	//{
	//	CUSTOM->SaveFile();
	//}
}

void CustomMapScene::SetStateDraw()
{
	//DrawString(0, 0, L"Set", 0xffffff);
	//DrawString(0, STRING_HIGHT, L"マップの横幅：", 0xffffff);
	//DrawString(0, STRING_HIGHT+LINE_SPACING, L"マップの高さ：", 0xffffff);
	//DrawString(0, STRING_HIGHT + LINE_SPACING*2, L"ファイル名：", 0xffffff);
	//DrawString(0, STRING_HIGHT*2 + LINE_SPACING*2, L"※次の文字とスペースは使用できません\n「￥　／　：　＊　？　”　＜　＞　｜　.　& ( ) [ ] { } ^ = ; ! ' + , ` ~」", 0xff9999);
	//int tmpFlag = 0;
	//// 横幅入力
	//mapSizeX_ = KeyInputNumber(GetDrawStringWidth(L"マップの横幅：", GetStringLength(L"マップの横幅：")) + 1, STRING_HIGHT, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	//if (mapSizeX_<MIN_MAP_SIZE || mapSizeX_>MAX_MAP_SIZE)
	//{
	//	return;
	//}
	//else
	//{
	//	tmpFlag++;
	//}
	//DrawFormatString(GetDrawStringWidth(L"マップの横幅：", GetStringLength(L"マップの横幅：")) + 1, STRING_HIGHT, 0xffffff, L"%d", mapSizeX_);
	//// 縦幅入力
	//mapSizeY_ = KeyInputNumber(GetDrawStringWidth(L"マップの高さ：", GetStringLength(L"マップの高さ：")) + 1, STRING_HIGHT+LINE_SPACING, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	//if (mapSizeY_<MIN_MAP_SIZE || mapSizeY_>MAX_MAP_SIZE)
	//{
	//	return;
	//}
	//else
	//{
	//	tmpFlag++;
	//}
	//DrawFormatString(GetDrawStringWidth(L"マップの高さ：", GetStringLength(L"マップの高さ：")) + 1, STRING_HIGHT + LINE_SPACING, 0xffffff, L"%d", mapSizeY_);
	//// 名前入力
	//if (KeyInputString(GetDrawStringWidth(L"ファイル名：", GetStringLength(L"ファイル名：")) + 1, STRING_HIGHT+LINE_SPACING*2, MAX_NAME_SIZE, fileName_, true) != 1)
	//{
	//	return;
	//}
	//else {
	//	// ファイル名に非対応文字が含まれているか
	//	if (FileNameErrorCheck(fileName_))
	//	{
	//		return;
	//	}
	//	tmpFlag++;
	//}
	//if (tmpFlag >= 3)
	//{
	//	nowState_= CustomState::MAP_CUSTOM;
	//	CUSTOM->SetUp(fileName_, VECTOR2(mapSizeX_, mapSizeY_));
	//}
}

void CustomMapScene::MapCustomDraw()
{
//	//DrawString(0, 0, L"Custom", 0xffffff);
//	// 枠表示
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
//	DrawRoundRect(SELECT_UI_POS.first.x, SELECT_UI_POS.first.y, SELECT_UI_POS.second.x, SELECT_UI_POS.second.y,20,20, 0x555555, true);
//	DrawRoundRect(SELECT_UI_POS.first.x, SELECT_UI_POS.first.y, SELECT_UI_POS.second.x, SELECT_UI_POS.second.y, 20, 20, 0xffffff, false);
//	DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0x555555, true);
//	DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0xffffff, false);
//	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
//	// 説明文の表示
//	DrawString(TEXT_UI_POS.first.x+30, TEXT_UI_POS.first.y+ (TEXT_UI_POS.second.y - TEXT_UI_POS.first.y) / 5,_StW(textData_[selChip_]).c_str(), 0xffffff);
//	VECTOR2 mPos = lpMouseController.GetPos();
//	// とりあえずボタンの表示
//	/*int shadowOffset = 3;
//	int pushuOffset = 1;
//	for (auto list : bList_)
//	{
//		if (list.pushFlag)
//		{
//			DrawRoundRect(list.luPos.x+ pushuOffset, list.luPos.y+ pushuOffset, list.rdPos.x+ pushuOffset, list.rdPos.y+ pushuOffset, 10, 10, list.CorH, true);
//
//		}
//		else
//		{
//			DrawRoundRect(list.luPos.x + shadowOffset, list.luPos.y + shadowOffset, list.rdPos.x + shadowOffset, list.rdPos.y + shadowOffset, 10, 10, 0x000000, true);
//			DrawRoundRect(list.luPos.x, list.luPos.y, list.rdPos.x, list.rdPos.y, 10, 10, list.CorH, true);
//
//		}
//	
//	}*/
//	for (auto&& list : button_)
//	{
//		list->Draw();
//	}
//	for (auto list : buttonText_)
//	{
//		DrawString(list.pos_.x, list.pos_.y, _StW(list.str_).c_str(), list.color_);
//	}
//#ifdef _DEBUG
//
//	DrawFormatString(mPos.x, mPos.y+10, 0x00ff00, L"%d:%d", mPos.x, mPos.y);
//	DrawFormatString(mPos.x, mPos.y + 30, 0x0000ff, L"%d:%d", mPos.x + static_cast<int>(lpApplication.GetCamera().GetPos().x), mPos.y + static_cast<int>(lpApplication.GetCamera().GetPos().y));
//#endif // _DEBUG
//
//
//

//		}
//		else
//		{
//			DrawRoundRect(list.luPos.x + shadowOffset, list.luPos.y + shadowOffset, list.rdPos.x + shadowOffset, list.rdPos.y + shadowOffset, 10, 10, 0x000000, true);
//			DrawRoundRect(list.luPos.x, list.luPos.y, list.rdPos.x, list.rdPos.y, 10, 10, list.CorH, true);
//
//		}
//	
//	}*/
//	for (auto&& list : button_)
//	{
//		list->Draw();
//	}
//	for (auto& list : buttonText_)
//	{
//		DrawString(list.pos_.x, list.pos_.y, _StW(list.str_).c_str(), list.color_);
//	}
//#ifdef _DEBUG
//
//	DrawFormatString(mPos.x, mPos.y+10, 0x00ff00, L"%d:%d", mPos.x, mPos.y);
//	DrawFormatString(mPos.x, mPos.y + 30, 0x0000ff, L"%d:%d", mPos.x + static_cast<int>(lpApplication.GetCamera().GetPos().x), mPos.y + static_cast<int>(lpApplication.GetCamera().GetPos().y));
//#endif // _DEBUG

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

bool CustomMapScene::LoadText()
{
	tinyxml2::XMLDocument doc;
	auto error=doc.LoadFile("data/textData.xml");
	if (error != tinyxml2::XML_SUCCESS)
	{
		return false;
	}
	textData_.try_emplace( MapChipName::MAINSTAY ,doc.FirstChildElement("mainstay")->GetText() );
	textData_.try_emplace( MapChipName::SPAWNER ,doc.FirstChildElement("spawner")->GetText() );
	textData_.try_emplace( MapChipName::ROOT ,doc.FirstChildElement("root")->GetText() );
	textData_.try_emplace( MapChipName::FIELD ,doc.FirstChildElement("field")->GetText() );
	textData_.try_emplace( MapChipName::WALL ,doc.FirstChildElement("wall")->GetText() );

	return true;
}
