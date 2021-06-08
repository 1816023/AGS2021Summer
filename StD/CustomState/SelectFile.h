#pragma once
#include "../Button/RectButton.h"
#include "../tinyxml2/tinyxml2.h"
#include "CustomState.h"
#include "../Scene/CustomMapScene.h"
#include "../File/FileSystem.h"


struct DataState
{
	std::string fileName;
	VECTOR2 mapSize;

};
struct SelectFile:public CustomStateBase
{
	SelectFile() {}
	~SelectFile()override {}

	bool Init(CustomMapScene* scene)override
	{
		scene->mapSizeX_ = 0;
		scene->mapSizeY_ = 0;
		scene->fileName_[0] = TCHAR();
		FileSystem::serch("data/mapData", fileList_);
		int a = 0;
		for (auto list : fileList_)
		{
			auto data = GetData("data/mapData/" + list);
			// 開けなかったファイル
			if (data.fileName == "" || data.mapSize.x < 0 || data.mapSize.y < 0)
			{
				continue;
			}
			// 開いちゃダメなファイル
			if (list == "defalt_map.xml" || list == "sample_data.xml")
			{
				continue;
			}
			buttomList_.emplace_back(std::make_unique<RectButton>(VECTOR2(0, 50), VECTOR2(300, 70), 0xffffff, [&]() {return true; }, VECTOR2(10 + a / 14 * 310, a % 14 * 30)));
			buttomList_.back()->SetAuto();
			buttomList_.back()->SetReversePush();
			buttomList_.back()->SetString(list + "：" + std::to_string(data.mapSize.x) + "：" + std::to_string(data.mapSize.y), VECTOR2(5,2));
			a++;
		}
		VECTOR2 sSize;
		int bit;
		GetScreenState(&sSize.x, &sSize.y, &bit);
		isNewCreate_ = false;
		buttomList_.emplace_back(std::make_unique<RectButton>(VECTOR2(sSize.x / 1.25, 10), VECTOR2(sSize.x / 1.25 + 100, 30), 0xffffff, [&]() {isNewCreate_ = true; return true; }, VECTOR2(0, 0)));
		buttomList_.back()->SetString("新規作成", VECTOR2(12, 2));
		buttomList_.back()->SetAuto();
		return true;
	}
	void Update(CustomMapScene* scene)override
	{
		for (auto&& list : buttomList_)
		{
			list->Update();
		}
		if (isNewCreate_)
		{
			scene->nowState_ = CustomState::SET_STATE;
			scene->custom_[scene->nowState_]->Init(scene);
		}
	}
	void Draw(CustomMapScene* scene)override
	{
		VECTOR2 sSize;
		int bit;
		GetScreenState(&sSize.x, &sSize.y, &bit);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 128);
		DrawRoundRect(0, 0, sSize.x, sSize.y, 30, 30, 0xffffff, true);
		DrawRoundRect(0, 0, sSize.x, sSize.y, 30, 30, 0x000000, false);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
		for (auto&& list : buttomList_)
		{
			list->Draw();
		}

	}
private:
	DataState GetData(std::string path) {
		tinyxml2::XMLDocument doc;
		auto error = doc.LoadFile(path.c_str());
		if (error != tinyxml2::XML_SUCCESS)
		{
			return DataState{ "",{-1,-1} };
		}
		DataState state;
		state.fileName = path;
		auto elm = doc.FirstChildElement("map");
		state.mapSize.y = elm->FindAttribute("hight")->IntValue();
		state.mapSize.x = elm->FindAttribute("hight")->Next()->IntValue();
		error = doc.SaveFile(path.c_str());
		if (error != tinyxml2::XML_SUCCESS)
		{
			return DataState{ "",{-1,-1} };
		}
		return state;
	}
	std::list<std::string>fileList_;
	std::list<std::unique_ptr<Button>>buttomList_;
	bool isNewCreate_;

};