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
	if (0 > pos.x || pos.x > mapSize_.x * chipSize_.x)
	{
		return false;
	}
	if (0 > pos.y || pos.y > mapSize_.y * chipSize_.y)
	{
		return false;
	}
	VECTOR2 mapPos = pos / chipSize_;
	if (mapData_.size() < mapPos.y && mapData_[mapPos.y].size() < mapPos.x)
	{
		mapData_[mapPos.y][mapPos.x] = chip;
		return true;
	}
	
	return false;
}
