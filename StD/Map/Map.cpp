#include <DxLib.h>
#include <sstream>
#include <array>
#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

int Map::Update()
{
	return 0;
}

void Map::Draw()
{
	std::array<int, 5> color = {
		0x007fff,			// 防衛拠点				青
		0xff0f0f,			// 敵出現位置			赤
		0xafff00,			// 敵侵攻ルート			緑
		0xe3e3e3,			// 自機配置可能箇所		白
		0x000000			// 自機配置不可能箇所	黒（背景色）
	};
	for (int y = 0; y < state_.mapSize_.y; y++)
	{
		for (int x = 0; x < state_.mapSize_.x; x++)
		{
			if (mapData_[y][x]!=MapChipName::WALL)
			{
				DrawBox(x * state_.chipSize_.x , y * state_.chipSize_.y , x * state_.chipSize_.x  + state_.chipSize_.x , y * state_.chipSize_.y + state_.chipSize_.y , color[static_cast<int>(mapData_[y][x]) - 1], true);
			}
#ifdef _DEBUG
			DrawFormatString(x * state_.chipSize_.x , y * state_.chipSize_.y , 0xffffff, (L"%d"), (static_cast<int>(mapData_[y][x])));
#endif // _DEBUG

		}
	}
	for (int x = 0; x <= state_.mapSize_.x; x++)
	{
		DrawLine(x * state_.chipSize_.x, 0, x * state_.chipSize_.x, state_.chipSize_.x * state_.mapSize_.y, 0xffffff);
	}
	for (int y = 0; y <= state_.mapSize_.y; y++)
	{
		DrawLine(0, y * state_.chipSize_.y, state_.chipSize_.x * state_.mapSize_.x, y * state_.chipSize_.y, 0xffffff);
	}
	
}

bool Map::SetUp(std::string mapName)
{
	if (!Map::LoadMap(mapName))
	{
		return false;
	}
	const tinyxml2::XMLElement* mapElm = document_.FirstChildElement("map");
	state_.mapSize_ = { mapElm->IntAttribute("hight"),mapElm->IntAttribute("width") };
	const tinyxml2::XMLElement* chipElm = document_.FirstChildElement("chip");
	state_.chipSize_ = { chipElm->IntAttribute("hight"), chipElm->IntAttribute("width") };
	dataVec mapData;
	mapData.resize(state_.mapSize_.y);
	//for (int y = 0; y < mapSize_.y; y++)
	//{
	//	mapData_[y].resize(mapSize_.y);
	//}
	std::string mapStr = mapElm->GetText();
	std::stringstream ss{ mapStr };
	std::string buf;
	int y = 0;
	while (std::getline(ss, buf, ','))
	{
		mapData[y].push_back(static_cast<MapChipName>(std::atoi(buf.c_str())));
		if (mapData[y].size()>=state_.mapSize_.x)
		{
			y++;
		}
	}
	mapData_ = mapData;
	return true;
}

MapChipName Map::GetMapChip(Vec2Float pos)
{
	VECTOR2 vec = { static_cast<int>(pos.x) / state_.chipSize_.x,static_cast<int>(pos.y) / (state_.chipSize_.y) };
	if (vec.x < 0 || vec.y < 0)
	{
		return MapChipName::MAX;
	}
	if (vec.x >= state_.mapSize_.x || vec.y >= state_.mapSize_.y)
	{
		return MapChipName::MAX;
	}
	
	return mapData_[vec.y][vec.x];
}

MapChipName Map::GetMapChip(VECTOR2 pos)
{
	VECTOR2 vec = pos / (state_.chipSize_);
	if (vec.x < 0 || vec.y < 0)
	{
		return MapChipName::MAX;
	}
	if (vec.x >= state_.mapSize_.x|| vec.y >= state_.mapSize_.y)
	{
		return MapChipName::MAX;
	}

	return mapData_[vec.y][vec.x];
}

VECTOR2 Map::GetMapSize()
{
	return state_.mapSize_;
}

VECTOR2 Map::GetChipSize()
{
	return state_.chipSize_;
}

bool Map::LoadMap(std::string mapName)
{
	auto path = "./data/mapData/" + mapName+".xml";
	auto error = document_.LoadFile(path.c_str());
	if (error != tinyxml2::XML_ERROR_FILE_NOT_FOUND)
	{
		return true;
	}
	return false;
}
