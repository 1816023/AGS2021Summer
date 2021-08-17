#pragma once
#include "CustomState.h"
struct RootCustom :
	public CustomStateBase
{
	RootCustom() {};
	~RootCustom()override {};
	bool Init(CustomMapScene* scene) override
	{
		dirChip_ = RootDir::MAX;
		const TCHAR* fontName = L"rootButton";
		const int bSize = 64;
		const int bSpace = 20;
		VECTOR2 roundS = { 10, 10 };
		lpFontMng.AddStrFont(bSize, fontName);
		int id=0;
		// ボタンの作成
		// up
		auto* button = (new RoundRectButton(VECTOR2(bSpace, bSpace * 2), VECTOR2(bSize, bSize), roundS, 0x007fff, [&]() {dirChip_ = RootDir::UP; return true; }));
		button->SetAuto();
		button->SetReversePush();
		button->SetString("↑", VECTOR2(), lpFontMng.GetStrFont(fontName));
		scene->canvas_->AddUIByID(button, id++);
		// down
		button = (new RoundRectButton(VECTOR2(bSize + bSpace * 2, bSpace * 2), VECTOR2(bSize, bSize), roundS, 0xff0f0f, [&]() {dirChip_ = RootDir::DOWN; return true; }));
		button->SetAuto();
		button->SetReversePush();
		button->SetString("↓", VECTOR2(), lpFontMng.GetStrFont(fontName));
		scene->canvas_->AddUIByID(button, id++);
		// right
		button = (new RoundRectButton(VECTOR2(bSize * 2 + bSpace * 3, bSpace * 2), VECTOR2(bSize, bSize), roundS, 0xfff00, [&]() {dirChip_ = RootDir::RIGHT; return true; }));
		button->SetAuto();
		button->SetReversePush();
		button->SetString("→", VECTOR2(), lpFontMng.GetStrFont(fontName));
		scene->canvas_->AddUIByID(button, id++);
		// left
		button = (new RoundRectButton(VECTOR2(bSpace, bSize + bSpace * 3), VECTOR2(bSize, bSize), roundS, 0xe3e3e3, [&]() {dirChip_ = RootDir::LEFT; return true; }));
		button->SetAuto();
		button->SetReversePush();
		button->SetString("←", VECTOR2(), lpFontMng.GetStrFont(fontName));
		scene->canvas_->AddUIByID(button, id++);
		// save
		int sbSize = bSize / 2;
		button = new RoundRectButton(VECTOR2(bSpace * 3 + bSize * 2, bSize * 2 + bSpace * 4), VECTOR2(bSize, sbSize), roundS, 0xffffff, [&,scene]() {Save(scene); return true; });
		button->SetAuto();
		button->SetReversePush();
		button->SetString("Save", VECTOR2(10,5));
		scene->canvas_->AddUIByID(button, id++);
		// next
		button = new RoundRectButton(VECTOR2(bSpace*2+bSize, bSize * 2 + bSpace * 4), VECTOR2(bSize, sbSize), roundS, 0xffffff, [&, scene]() {Next(scene); return true; });
		button->SetAuto();
		button->SetReversePush();
		button->SetString("Next", VECTOR2(10, 5));
		scene->canvas_->AddUIByID(button, id++);
		// back
		button = new RoundRectButton(VECTOR2(bSpace, bSize * 2 + bSpace * 4), VECTOR2(bSize, sbSize), roundS, 0xffffff, [&, scene]() {Back(scene); return true; });
		button->SetAuto();
		button->SetReversePush();
		button->SetString("Back", VECTOR2(10, 5));
		scene->canvas_->AddUIByID(button, id++);

		// スピンボックスの作成
		auto spinBox = new SpinBoxForInt(VECTOR2(bSize + bSpace * 2, bSize + bSpace * 3), bSize * 2, SELECT_UI_POS.first, lpFontMng.GetStrFont(fontName));
		for (int a = 99; a > 0; a--)
		{
			spinBox->AddData(a);
		}
		spinBox->StartEnd(false);
		scene->canvas_->AddUIByName(spinBox, L"rootSpin");

		// ルート管理用の変数の設定
		for (int a = 0; a < 100; a++)
		{
			rootMap_[a].resize(scene->cusMap_->GetMapSize().y);

			for (auto& vec : rootMap_[a])
			{
				for (int x = 0; x < scene->cusMap_->GetMapSize().x; x++)
				{
					vec.push_back(RootDir::MAX);
				}
			}
		}


		return true;
	}
	void Update(CustomMapScene* scene) override
	{
		VECTOR2 mPos = lpMouseController.GetPos();
		VECTOR2 mcPos = lpMouseController.GetOffsetPos();
		int spin = dynamic_cast<SpinBoxForInt*>(scene->canvas_->GetUIByName(L"rootSpin"))->GetSelData();
		if (lpMouseController.GetClickTrg(MOUSE_INPUT_LEFT))
		{
			if (mPos.x < SELECT_UI_POS.first.x)
			{
				if (scene->cusMap_->GetMapChip(mcPos) == MapChipName::ROOT||scene->cusMap_->GetMapChip(mcPos)==MapChipName::SPAWNER)
				{
					VECTOR2 key=mcPos/scene->cusMap_->GetChipSize();
					rootMap_[spin][key.y][key.x] = dirChip_;
				}
			}
		}

	}
	void Draw(CustomMapScene* scene)override
	{
		const TCHAR* font = L"rootButton";
		const int allowSize = GetFontSizeToHandle(lpFontMng.GetStrFont(font));
		std::map<RootDir, std::wstring>allowStr;

		allowStr.try_emplace(RootDir::UP, L"↑");
		allowStr.try_emplace(RootDir::DOWN, L"↓");
		allowStr.try_emplace(RootDir::RIGHT, L"→");
		allowStr.try_emplace(RootDir::LEFT, L"←");
		allowStr.try_emplace(RootDir::MAX, L"・");
		int spin = dynamic_cast<SpinBoxForInt*>(scene->canvas_->GetUIByName(L"rootSpin"))->GetSelData();

		for (int y = 0; y < rootMap_[spin].size(); y++)
		{
			for (int x = 0; x < rootMap_[spin][y].size(); x++)
			{
				DrawStringToHandle(x * allowSize, y * allowSize, allowStr[rootMap_[spin][y][x]].c_str(), 0x000000, lpFontMng.GetStrFont(font));
			}
		}

	}
	void DrawUI(CustomMapScene* scene) override
	{

	}
	void Delete() override
	{
		for (auto& array : rootMap_)
		{
			array.clear();
		}
	}
private:
	bool Save(CustomMapScene* scene)
	{
		tinyxml2::XMLDocument doc;
		scene->cusMap_->GetDoc(doc);
		tinyxml2::XMLElement* rootElm = doc.FirstChildElement("root");
		rootElm->DeleteChildren();
		for (int a = 0; a < rootMap_.size(); a++)
		{
			bool check=false;
			for (auto y : rootMap_[a])
			{
				for (auto x : y)
				{
					check = (x != RootDir::MAX ? true : check);
				}
			}
			if (!check)
			{
				continue;
			}
			auto* newElm = rootElm->InsertNewChildElement("root");
			newElm->SetAttribute("id", a);

			
		}
		scene->cusMap_->SaveXMLFile(doc);
		return true;
	}
	bool Next(CustomMapScene* scene)
	{
		if (!Save(scene))
		{
			return false;
		}
		scene->canvas_->ClearUI();
		scene->textCanvas_->ClearUI();
		scene->nowState_ = CustomState::ENEMY_CUSTOM;
		scene->custom_[scene->nowState_]->Init(scene);
		Delete();

		return true;
	}
	bool Back(CustomMapScene* scene)
	{
		scene->canvas_->ClearUI();
		scene->textCanvas_->ClearUI();
		scene->nowState_ = CustomState::MAP_CUSTOM;
		scene->custom_[scene->nowState_]->Init(scene);
		Delete();
		return true;
	}
	bool CheckRoot(CustomMapScene* scene)
	{
		auto mainStay=scene->cusMap_->GetMainStay();
		auto spawners = scene->cusMap_->GetSpawner();
		std::function<bool(RootDir,VECTOR2)>check = [&](RootDir root,VECTOR2 dir) {
			switch (root)
			{
			case RootDir::UP:
				
				break;
			case RootDir::DOWN:

				break;
			case RootDir::RIGHT:

				break;
			case RootDir::LEFT:

				break;
			case RootDir::MAX:
				break;
			default:
				break;
			}
			return true;
		};
		for (int s = 0; s < spawners.size(); s++)
		{
			
		}
	}
	RootDir dirChip_;
	std::array<std::vector<rootVec>,100>rootMap_;
};

