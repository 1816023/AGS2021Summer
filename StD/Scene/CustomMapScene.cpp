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
#include "../CustomState/RootCustom.h"
#include "../StringUtil.h"
#include "../Map/Astar.h"
#include "../MapEnum.h"
#include "../GUI/Canvas.h"

CustomMapScene::CustomMapScene()
{
	Init();
}

CustomMapScene::~CustomMapScene()
{
	for (auto&& custom : custom_)
	{
		custom.second->Delete();
	}
	alwaysCanvas_->ClearUI();
}

unique_Base CustomMapScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);

	if (isTitleTransition_)
	{
		return std::make_unique<TitleScene>();
	}
	canvas_->Update();
	textCanvas_->Update();
	alwaysCanvas_->Update();
	custom_[nowState_]->Update(this);
	return std::move(own);
}

bool CustomMapScene::Init()
{
	auto defSize = VECTOR2(DEF_SCREEN_SIZE_X, DEF_SCREEN_SIZE_Y);
	canvas_ = std::make_unique<Canvas>(SELECT_UI_POS.first, defSize - SELECT_UI_POS.first, BackType::RoundRect);
	alwaysCanvas_ = std::make_unique<Canvas>(VECTOR2(0, 0), defSize,BackType::Non);
	textCanvas_ = std::make_unique<Canvas>(TEXT_UI_POS.first, VECTOR2(SELECT_UI_POS.first.x,defSize.y- TEXT_UI_POS.first.y), BackType::RoundRect);	cusMap_ = std::make_unique<Custom>();
	nowState_ = CustomState::SELECT_FILE;
	custom_.try_emplace(CustomState::SELECT_FILE, std::make_unique<SelectFile>());
	custom_.try_emplace(CustomState::SET_STATE, std::make_unique<SetState>());
	custom_.try_emplace(CustomState::MAP_CUSTOM, std::make_unique<MapCustom>());
	custom_.try_emplace(CustomState::ROOT_CUSTOM, std::make_unique<RootCustom>());
	custom_.try_emplace(CustomState::ENEMY_CUSTOM, std::make_unique<EnemyCustom>());
	custom_.try_emplace(CustomState::END_CUSTOM, std::make_unique<EndCustom>());
	auto* button = new RoundRectButton(VECTOR2(0, 0), VECTOR2(34, 34), VECTOR2(5, 5), 0xff00ff, [&]() {isTitleTransition_ = true; return true; });
	button->SetAuto();
	button->SetReversePush();
	alwaysCanvas_->AddUIByID(button, 10);
	custom_[nowState_]->Init(this);
	isTitleTransition_ = false;
	lpApplication.GetCamera().ScaleLock(false);
	return true;
}

void CustomMapScene::Draw()
{
	Vec2Float cPos = Application::Instance().GetCamera().GetPos();
	VECTOR2 mPos = lpMouseController.GetPos();
	if (nowState_ == CustomState::MAP_CUSTOM || nowState_ == CustomState::ENEMY_CUSTOM ||nowState_==CustomState::ROOT_CUSTOM)
	{
		cusMap_->Draw();
#ifdef _DEBUG
		DrawFormatString(mPos.x + static_cast<int>(cPos.x), mPos.y + static_cast<int>(cPos.y) - 10, 0xffffff, L"%d", static_cast<int>(cusMap_->GetMapChip((mPos + cPos))));
#endif // DEBUG
		if (!lpMouseController.IsHitBoxToMouse(SELECT_UI_POS.first, SELECT_UI_POS.second) && !lpMouseController.IsHitBoxToMouse(TEXT_UI_POS.first, TEXT_UI_POS.second))
		{
			if (lpMouseController.IsHitBoxToMouse(VecICast((VECTOR2(0, 0)) - cPos), VecICast(cusMap_->GetMapSize() - cPos * cusMap_->GetChipSize())))
			{
				mPos = VecICast(mPos + cPos) / (cusMap_->GetChipSize()) * (cusMap_->GetChipSize());
				SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, std::abs(128 - blendAlpha_ % 256));
				DrawBox(mPos.x, mPos.y, (mPos.x) + cusMap_->GetChipSize().x, (mPos.y) + cusMap_->GetChipSize().y, 0xcccc00, true);
				SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
			}
		}
	}
	custom_[nowState_]->Draw(this);

}

void CustomMapScene::DrawUI()
{
	
	canvas_->Draw();
	textCanvas_->Draw();
	custom_[nowState_]->DrawUI(this);
	alwaysCanvas_->Draw();

	//const auto& mainStay = cusMap_->GetMainStay();
	//int cnt = 0;
	//auto mapSize = cusMap_->GetMapSize().x;
	//for (auto& ms : mainStay)
	//{
	//	auto y = ms / mapSize;
	//	DrawFormatString(0, 48 + 16 * cnt, 0xffffff, L"mainStay%d = x %d, y %d", cnt + 1, ms - y * mapSize, y);
	//	cnt++;
	//}
	//const auto& spawners = cusMap_->GetSpawner();
	//for (auto& sp : spawners)
	//{
	//	auto y = sp / mapSize;
	//	DrawFormatString(0, 48 + 16 * cnt, 0xffffff, L"spawner%d = x %d, y %d", cnt + 1 - static_cast<int>(mainStay.size()), sp - y * mapSize, y);
	//	cnt++;
	//}

}

ErrorCode CustomMapScene::SaveCheck()
{
	int mainStayNum = 0;
	int spawnerNum = 0;
	for (int y = 0; y < cusMap_->GetMapSize().y; y++)
	{
		for (int x = 0; x < cusMap_->GetMapSize().x; x++)
		{
			auto chip = cusMap_->GetMapChip(VECTOR2(x, y) * cusMap_->GetChipSize());
			mainStayNum += (MapChipName::MAINSTAY == chip ? 1 : 0);
			spawnerNum += (MapChipName::SPAWNER == chip ? 1 : 0);

		}
	}
	if (mainStayNum >= 3 && spawnerNum >= 3)
	{
		return ErrorCode::MsSpError;
	}
	else if (mainStayNum >= 3)
	{
		return ErrorCode::MsError;
	}
	else if (spawnerNum >= 3)
	{
		return ErrorCode::SpError;
	}
	else
	{
		return ErrorCode::NoError;
	}
	return ErrorCode::NoError;
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

bool CustomMapScene::LoadText(std::string type)
{
	tinyxml2::XMLDocument doc;
	auto error = doc.LoadFile("data/textData.xml");
	if (error != tinyxml2::XML_SUCCESS)
	{
		return false;
	}
	if (type == "map")
	{
		auto elm = doc.FirstChildElement(type.c_str());
		textData_.try_emplace(MapChipName::MAINSTAY, elm->FirstChildElement("mainstay")->GetText());
		textData_.try_emplace(MapChipName::SPAWNER, elm->FirstChildElement("spawner")->GetText());
		textData_.try_emplace(MapChipName::ROOT, elm->FirstChildElement("root")->GetText());
		textData_.try_emplace(MapChipName::FIELD, elm->FirstChildElement("field")->GetText());
		textData_.try_emplace(MapChipName::WALL, elm->FirstChildElement("wall")->GetText());
	}
	else if ("Enemy")
	{
		auto elm = doc.FirstChildElement(type.c_str());
		textData_.try_emplace(MapChipName::MAINSTAY, elm->FirstChildElement("mainstay")->GetText());
		textData_.try_emplace(MapChipName::SPAWNER, elm->FirstChildElement("spawner")->GetText());
		textData_.try_emplace(MapChipName::ROOT, elm->FirstChildElement("root")->GetText());
		textData_.try_emplace(MapChipName::FIELD, elm->FirstChildElement("field")->GetText());
		textData_.try_emplace(MapChipName::WALL, elm->FirstChildElement("wall")->GetText());

	}
	else
	{
		return false;
	}
	return true;
}
