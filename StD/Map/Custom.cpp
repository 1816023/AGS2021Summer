#include "Custom.h"
#include <fstream>
#include <Windows.h>
#include "../StringUtil.h"
Custom::Custom(VECTOR2 offset):offset_(offset)
{
}

Custom::~Custom()
{
}

void Custom::SetUp(std::wstring fileName, VECTOR2 mapSize)
{
	state_.mapSize_ = mapSize;
	state_.chipSize_ = { 64,64 };
	mapData_.resize(mapSize.y);
	state_.name_ = fileName;
	for (auto& map : mapData_)
	{
		while( map.size() < state_.mapSize_.x )
		{
			map.push_back(MapChipName::WALL);
		}
		
	}
	CreateMapFile(mapSize, fileName);
}

bool Custom::SetChip(VECTOR2 pos, MapChipName chip)
{
	if (0 > pos.x || pos.x > state_.mapSize_.x * state_.chipSize_.x)
	{
		return false;
	}
	if (0 > pos.y || pos.y > state_.mapSize_.y * state_.chipSize_.y)
	{
		return false;
	}
	VECTOR2 mapPos = pos / state_.chipSize_;
	if (mapData_.size() > mapPos.y && mapData_[mapPos.y].size() > mapPos.x)
	{
		mapData_[mapPos.y][mapPos.x] = chip;
		return true;
	}
	
	return false;
}

bool Custom::CreateMapFile(VECTOR2 mapSize, std::wstring name)
{
	std::ifstream sample;
	sample.open("data/mapData/sample_data.xml");
	if (!sample)
	{
		return false;
	}
	std::string filePath = "data/mapData/" + StringUtil::WStringToString(name) + ".xml";
	std::ofstream file;
	file.open(filePath.c_str());
	if (!file)
	{
		return false;
	}
	file << sample.rdbuf() << std::flush;
	sample.close();
	file.close();
	auto error = document_.LoadFile(filePath.c_str());
	if (error != tinyxml2::XML_SUCCESS)
	{
		return false;
	}
	tinyxml2::XMLElement* mapElm= document_.FirstChildElement("map");
	mapElm->SetAttribute("hight", mapSize.x);
	mapElm->SetAttribute("width", mapSize.y);
	std::string mapData="\n";
	for (auto& y : mapData_)
	{
		for (auto& data : y)
		{
			mapData += std::to_string(static_cast<char>(data));
			mapData += ",";
			
		}
		mapData += "\n";
	}
	mapElm->SetText(mapData.c_str());

	error=document_.SaveFile(filePath.c_str());
	if (error)
	{
		return false;
	}
	return true;
}

