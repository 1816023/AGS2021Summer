#include "Simple.h"
#include<DxLib.h>
#include<sstream>
#include<cassert>
#include<array>
Simple::Simple(VECTOR2 pos)
{
	pos_ = pos;
	screen_=MakeScreen(DEFAULT_SCREEN_SIZE_X, DEFAULT_SCREEN_SIZE_X, 0);
}

Simple::~Simple()
{
	DeleteGraph(screen_);
}

int Simple::Update()
{
	return 0;
}

void Simple::Draw()
{
	const VECTOR2 rectSize=mapList_[listKey_].chip/2*mapList_[listKey_].mapSize;
	DrawRectExtendGraph(pos_.x-size_.x/2, pos_.y-size_.y/2, pos_.x + size_.x/2, pos_.y + size_.y/2, 0, 0, rectSize.x, rectSize.y, screen_, false);
	DrawLine(pos_.x - size_.x / 2, pos_.y - size_.y / 2, pos_.x - size_.x / 2, pos_.y + size_.y / 2, 0xffffff);
	DrawLine(pos_.x - size_.x / 2, pos_.y - size_.y / 2, pos_.x + size_.x / 2, pos_.y - size_.y / 2, 0xffffff);
	DrawLine(pos_.x + size_.x / 2, pos_.y - size_.y / 2, pos_.x + size_.x / 2, pos_.y + size_.y / 2, 0xffffff);
	DrawLine(pos_.x - size_.x / 2, pos_.y + size_.y / 2, pos_.x + size_.x / 2, pos_.y + size_.y / 2, 0xffffff);
}

bool Simple::SetUp(std::list<std::string> name)
{
	for (auto list : name)
	{
		if (!Map::LoadMap(list))
		{
			return false;
		}
		if (!CheckData(list))
		{
			break;
		}
		
		SimpleMapState state;
		state.path = list;
		const tinyxml2::XMLElement* mapElm = document_.FirstChildElement("map");
		state.mapSize = { mapElm->IntAttribute("hight"),mapElm->IntAttribute("width") };
		const tinyxml2::XMLElement* chipElm = document_.FirstChildElement("chip");
		state.chip = { chipElm->IntAttribute("hight"), chipElm->IntAttribute("width") };
		dataVec mapData;
		mapData.resize(state.mapSize.y);
		std::string mapStr = mapElm->GetText();
		std::stringstream ss{ mapStr };
		std::string buf;
		int y = 0;
		while (std::getline(ss, buf, ','))
		{
			mapData[y].push_back(static_cast<MapChipName>(std::atoi(buf.c_str())));
			if (mapData[y].size() >= state.mapSize.x)
			{
				y++;
			}
		}
		state.mapData = mapData;
		mapList_.try_emplace(list, state);

		auto fPath = "./data/mapData/" + list;
		document_.SaveFile(fPath.c_str());
	}
	return true;
}

void Simple::SetSize(VECTOR2 size)
{
	size_ = size;
}

bool Simple::SetMap(std::string path)
{
	if (listKey_ == path)
	{
		return true;
	}
	listKey_ = path;
	auto defScreen = GetDrawScreen();
	SetDrawScreen(screen_);
	ClearDrawScreen();
	std::array<int, 5> color = {
	0x007fff,			// 防衛拠点				青
	0xff0f0f,			// 敵出現位置			赤
	0xafff00,			// 敵侵攻ルート			緑
	0xe3e3e3,			// 自機配置可能箇所		白
	0x000000			// 自機配置不可能箇所	黒（背景色）
	};
	for (int y = 0; y < mapList_[listKey_].mapSize.y; y++)
	{
		for (int x = 0; x < mapList_[listKey_].mapSize.x; x++)
		{
			if (mapList_[listKey_].mapData[y][x] != MapChipName::WALL)
			{
				DrawBox(x * mapList_[listKey_].chip.x/2, y * mapList_[listKey_].chip.y/2, x * mapList_[listKey_].chip.x/2 + mapList_[listKey_].chip.x/2, y * mapList_[listKey_].chip.y/2 + mapList_[listKey_].chip.y/2, color[static_cast<int>(mapList_[listKey_].mapData[y][x]) - 1], true);
			}
		}
	}
	//for (int x = 0; x <= mapList_[listKey_].mapSize.x; x++)
	//{
	//	DrawLine(x * mapList_[listKey_].chip.x, 0, x * mapList_[listKey_].chip.x, mapList_[listKey_].chip.x * mapList_[listKey_].mapSize.y, 0xffffff);
	//}
	//for (int y = 0; y <= mapList_[listKey_].mapSize.y; y++)
	//{
	//	DrawLine(0, y * mapList_[listKey_].chip.y, mapList_[listKey_].chip.x * mapList_[listKey_].mapSize.x, y * mapList_[listKey_].chip.y, 0xffffff);
	//}

	SetDrawScreen(defScreen);

	return false;
}
bool Simple::CheckData(std::string path) {
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
	if (error != tinyxml2::XML_SUCCESS)
	{
		assert(false);
		return false;
	}
	return true;
}
