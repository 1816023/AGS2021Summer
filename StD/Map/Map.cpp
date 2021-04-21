#include <DxLib.h>
#include <sstream>
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
	for (int x = 0; x <= state.mapSize_.x; x++)
	{
		DrawLine(x * state.chipSize_.x/2, 0, x * state.chipSize_.x/2, state.chipSize_.x/2 * state.mapSize_.y, 0xffffff);
	}
	for (int y = 0; y <= state.mapSize_.y; y++)
	{
		DrawLine(0, y * state.chipSize_.y/2, state.chipSize_.x/2 * state.mapSize_.x, y * state.chipSize_.y/2, 0xffffff);
	}
	for (int y = 0; y < state.mapSize_.y; y++)
	{
		for (int x = 0; x < state.mapSize_.x; x++)
		{
			DrawFormatString(x * state.chipSize_.x/2, y * state.chipSize_.y/2, 0xffffff, (L"%d"),(static_cast<int>(mapData_[y][x])));
		}
	}
}

bool Map::SetUp(std::string mapName)
{
	if (!Map::LoadMap(mapName))
	{
		return false;
	}
	const tinyxml2::XMLElement* mapElm = document.FirstChildElement("map");
	state.mapSize_ = { mapElm->IntAttribute("hight"),mapElm->IntAttribute("width") };
	const tinyxml2::XMLElement* chipElm = document.FirstChildElement("chip");
	state.chipSize_ = {128, 128};// { chipElm->IntAttribute("hight"), chipElm->IntAttribute("width") };
	mapData_.resize(state.mapSize_.y);
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
		
		mapData_[y].push_back(static_cast<MapChipName>(std::atoi(buf.c_str())));
		if (mapData_[y].size()>=state.mapSize_.x)
		{
			y++;
		}
		
	}
	return true;
}

MapChipName Map::GetMapChip(Vec2Float pos)
{
	VECTOR2 vec = { static_cast<int>(pos.x) / state.chipSize_.x,static_cast<int>(pos.y) / (state.chipSize_.y/2) };
	if (vec.x < 0 || vec.y < 0)
	{
		return MapChipName::MAX;
	}
	if (vec.x >= state.mapSize_.x || vec.y >= state.mapSize_.y)
	{
		return MapChipName::MAX;
	}
	
	return mapData_[vec.y][vec.x];
}

MapChipName Map::GetMapChip(VECTOR2 pos)
{
	VECTOR2 vec = pos / (state.chipSize_/2);
	if (vec.x < 0 || vec.y < 0)
	{
		return MapChipName::MAX;
	}
	if (vec.x >= state.mapSize_.x|| vec.y >= state.mapSize_.y)
	{
		return MapChipName::MAX;
	}

	return mapData_[vec.y][vec.x];
}

VECTOR2 Map::GetMapSize()
{
	return state.mapSize_;
}

VECTOR2 Map::GetChipSize()
{
	return state.chipSize_;
}

bool Map::LoadMap(std::string mapName)
{
	auto path = "./data/mapData/" + mapName+".xml";
	auto error = document.LoadFile(path.c_str());
	if (error != tinyxml2::XML_ERROR_FILE_NOT_FOUND)
	{
		return true;
	}
	return false;
}
