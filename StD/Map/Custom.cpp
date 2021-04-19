#include "Custom.h"

Custom::Custom()
{
}

Custom::~Custom()
{
}

void Custom::SetUp(std::wstring fileName, VECTOR2 mapSize)
{
	mapSize_ = mapSize;
	chipSize_ = { 64,64 };
	mapData_.resize(mapSize.y);
	for (auto& map : mapData_)
	{
		while( map.size() < mapSize_.x )
		{
			map.push_back(MapChipName::WALL);
		}
		
	}
}

bool Custom::SetChip(VECTOR2 pos, MapChipName chip)
{
	return false;
}
