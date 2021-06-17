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
	return true;
}

void CustomMapScene::Draw()
{
	Vec2Float cPos= Application::Instance().GetCamera().GetPos();
	cPos *= 2.0f;
	//DrawString(100, 100, L"CustomMapScene", 0xffffff);
	VECTOR2 mPos = lpMouseController.GetPos();

	if (nowState_ == CustomState::MAP_CUSTOM || nowState_ == CustomState::ENEMY_CUSTOM)
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
