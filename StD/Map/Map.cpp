#include <DxLib.h>
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


}

bool Map::SetUp(std::string mapName)
{
	Map::LoadMap(mapName);
	tinyxml2::XMLElement* elm = document.FirstChildElement("map");
	mapSize_.y = elm->IntAttribute("hight");
	mapSize_.x = elm->IntAttribute("width");
	return true;
}

void Map::LoadMap(std::string mapName)
{
	auto path = "./data/mapData/" + mapName+".xml";
	document.LoadFile(path.c_str());
}
