#include "GameMapSellectScene.h"
#include "../File/FileSystem.h"
#include "../tinyxml2/tinyxml2.h"
#include "../GUI/Button/ImageRectButton.h"
#include "../Scene/MainScene.h"
#include <cassert>
#include <DxLib.h>

GameMapSellectScene::GameMapSellectScene()
{
	std::list<std::string>fileList;
	if (!FileSystem::serch("./data/mapData/", fileList))
	{
		return;
	}
	pullDown_.push_back(new PullDown(VECTOR2(50,50), 500,CreateFontToHandle(NULL,25,10)));
	for (auto list:fileList)
	{
		if (CheckData(list))
		{
			pullDown_.back()->Add(list);
		}
	}
	transitionFlag_ = 0;
	map_ = std::make_unique<Simple>(VECTOR2(300,250));
	map_->SetSize({ 300,300 });
	map_->SetUp(fileList);
	map_->SetMap(pullDown_.back()->GetSelStr());
	button_.emplace_back(new ImageRectButton(VECTOR2(540,350), VECTOR2(100,70), L"./data/image/Back_Button1.png", L"./data/image/Back_Button1.png", [&]() {
		transitionFlag_ = 1;
		return true; }));
	button_.back()->SetAuto();
	button_.back()->SetScale(1.0f);
	button_.back()->SetString("back",VECTOR2(30,25));

	button_.emplace_back(new ImageRectButton(VECTOR2(640,350), VECTOR2(), L"./data/image/Back_Button2.png", L"./data/image/Back_Button2.png", [&]() {return true; }));

}

GameMapSellectScene::~GameMapSellectScene()
{
	for (auto list : pullDown_)
	{
		delete(list);
	}
	for (auto list : button_)
	{
		delete(list);
	}
}

unique_Base GameMapSellectScene::Update(unique_Base own)
{
	for (auto list : button_)
	{
		list->Update();
	}
	for (auto list : pullDown_)
	{
		list->Update();
	}
	map_->SetMap(pullDown_.back()->GetSelStr());
	switch (transitionFlag_)
	{
	case 0:
		break;
	case 1:
		return std::make_unique<MainScene>(true);
		break;
	case 2:
		break;
	default:
		break;
	}
	return std::move(own);
}

void GameMapSellectScene::Draw()
{
}

void GameMapSellectScene::DrawUI()
{
	for (auto list : button_)
	{
		list->Draw();
	}
	map_->Draw();

	for (auto list : pullDown_)
	{
		list->Draw();
	}

	std::vector<std::pair<int, std::string>>text =
	{
		{0xff0f0f,"敵出現"},
		{0x007fff,"自拠点"},
		{0xfff00,"敵侵攻"},
		{0xe3e3e3,"自機配置"},
		{0x333333,"設置不可"}
	};
	for (int y = 0; y < text.size(); y++)
	{
		DrawBox(600, 100+y*30, 600 + 20, 100 + 20+y*30, text[y].first, true);
		DrawBox(600, 100 + y * 30, 600 + 20, 100 + 20 + y * 30, 0xffffff, false);
		DrawString(600+30, 100 +y*30, _StW(text[y].second).c_str(), 0xffffff0);
	}
}

SCENE_ID GameMapSellectScene::GetScnID(void)
{
	return SCENE_ID::SELECT;
}

std::list<EnemyListState> GameMapSellectScene::LoadEnemyData(std::string path)
{
	return std::list<EnemyListState>();
}
bool GameMapSellectScene::CheckData(std::string path) {
	auto filepath = "./data/mapData/" + path;
	if (filepath.find("testMap") != filepath.npos || filepath.find("sample_data") != filepath.npos)
	{
		return false;
	}
	tinyxml2::XMLDocument doc;
	auto error = doc.LoadFile(filepath.c_str());
	if (error != tinyxml2::XML_SUCCESS)
	{
		assert(false);
		return false;
	}
	VECTOR2 vec2;
	auto elm = doc.FirstChildElement("map");
	vec2.x = elm->FindAttribute("hight")->IntValue();
	vec2.x = elm->FindAttribute("hight")->Next()->IntValue();
	if (VECTOR2() >= vec2)
	{
		return false;
	}
	error = doc.SaveFile(path.c_str());
	if (error != tinyxml2::XML_SUCCESS)
	{
		assert(false);
		return false;
	}
	return true;
}
