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
		cusMap_->Draw();
		#ifdef _DEBUG
		DrawFormatString(mPos.x + cPos.x, mPos.y + cPos.y - 10, 0xffffff, L"%d", static_cast<int>(cusMap_->GetMapChip((mPos + cPos))));
		#endif // DEBUG
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
	DrawFormatString(0, 48, 0xffffff, L"mainStay x %d, y %d", mainStay.at(1).x, mainStay.at(1).y);
}

int CustomMapScene::SaveCheck()
{
	int mainStayNum = 0;
	int spawnerNum = 0;
	for (int y = 0; y < cusMap_->GetMapSize().y; y++)
	{
		for (int x = 0; x < cusMap_->GetMapSize().x; x++)
		{
			auto chip = cusMap_->GetMapChip(VECTOR2(x, y) * cusMap_->GetChipSize());
			mainStayNum += (MapChipName::MAINSTAY ==chip  ? 1 : 0);
			spawnerNum += (MapChipName::SPAWNER == chip ? 1 : 0);

		}
	}
	if (mainStayNum >= 3 && spawnerNum >= 3)
	{
		return 1;
	}
	else if(mainStayNum>=3)
	{
		return 2;
	}
	else if(spawnerNum>=3)
	{
		return 3;
	}
	else
	{
		return 0;
	}
	return false;
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
	auto error=doc.LoadFile("data/textData.xml");
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
	else if("Enemy")
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
