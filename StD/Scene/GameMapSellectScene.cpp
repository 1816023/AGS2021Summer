#include "GameMapSellectScene.h"
#include "../File/FileSystem.h"
#include "../tinyxml2/tinyxml2.h"
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
	map_ = std::make_unique<Simple>(VECTOR2());
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
	for (auto list : pullDown_)
	{
		list->Draw();
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
