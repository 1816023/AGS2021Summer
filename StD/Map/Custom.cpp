#include "Custom.h"
#include <fstream>
#include <Windows.h>
#include <functional>
#include <sstream>
#include "../File/FileSystem.h"
#include "../StringUtil.h"
#include "../Application.h"
Custom::Custom(VECTOR2 offset):offset_(offset)
{
}

Custom::~Custom()
{
}

void Custom::SetUp(std::wstring fileName, VECTOR2 mapSize)
{
	if (fileName.find(L".xml") == fileName.npos)
	{
		fileName += L".xml";
	}
	state_.mapSize_ = mapSize;
	state_.chipSize_ = { 64,64 };
	mapData_.clear();
	mapData_.resize(mapSize.y);
	state_.name_ = fileName;
	if (!Map::SetUp(StringUtil::WStringToString(fileName)))
	{
		mapData_.resize(mapSize.y);
		for (auto& map : mapData_)
		{
			while (map.size() < state_.mapSize_.x)
			{
				map.push_back(MapChipName::WALL);
			}

		}
	}
	
	mainStay_ = { -1, -1 };
	int y = 0;
	// Ž©‹’“_‚ðŒŸõ‚·‚é
	for (auto map : mapData_)
	{
		auto find = std::find_if(map.begin(), map.end(), [](const MapChipName& data)
			{
				return data == MapChipName::MAINSTAY;
			});

		if (find != map.end())
		{
			mainStay_ = { static_cast<int>(std::distance(map.begin(),find)), y };
			break;
		}
		y++;
	}

	CreateMapFile(mapSize, fileName);
}

bool Custom::SetChip(VECTOR2 pos, MapChipName chip)
{
	if (0 > pos.x || pos.x > state_.mapSize_.x * state_.chipSize_.x)
	{
		return false;
	}
	if (0 > pos.y || pos.y > state_.mapSize_.y * state_.chipSize_.y )
	{
		return false;
	}
	VECTOR2 mapPos = pos / VECTOR2(state_.chipSize_.x,state_.chipSize_.y);
 	if (mapData_.size() > mapPos.y && mapData_[mapPos.y].size() > mapPos.x)
	{
		if (chip == MapChipName::MAINSTAY)
		{
			if (mainStay_ == VECTOR2(-1, -1))
			{
				mainStay_ = mapPos;
				mapData_[mapPos.y][mapPos.x] = chip;
			}
		}
		else
		{
			if (mainStay_ == mapPos)
			{
				mainStay_ = { -1, -1 };
			}
			mapData_[mapPos.y][mapPos.x] = chip != MapChipName::MAX ? chip : mapData_[mapPos.y][mapPos.x];
		}
		return true;
	}
	
	return false;
}

bool Custom::CreateMapFile(VECTOR2 mapSize, std::wstring name)
{
	std::list<std::string>fileList;
	FileSystem::serch("data/mapData", fileList);
	if (name.find(L".xml") == name.npos)
	{
		name += L".xml";
	}
	auto itr=std::find(fileList.begin(), fileList.end(),_WtS(name));
	std::string filePath = "data/mapData/" + _WtS(name);
	std::function<bool(int)>create = [&](int num) {
		std::ifstream sample;
		sample.open("data/mapData/sample_data.xml");
		if (!sample)
		{
			return false;
		}
		if (num != 0)
		{
			char tmp[256];
			sprintf_s(tmp, "%d", num);
			filePath="data/mapData/" + _WtS(name)+"("+tmp+")" + ".xml";

		}
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
		tinyxml2::XMLElement* mapElm = document_.FirstChildElement("map");
		mapElm->SetAttribute("hight", mapSize.x);
		mapElm->SetAttribute("width", mapSize.y);
		std::string mapData = "\n";
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

		error = document_.SaveFile(filePath.c_str());
		if (error)
		{
			return false;
		}
		return true;
	};
	if (itr == fileList.end())
	{
		return create(0);
	}
	else
	{
		
		auto error = document_.LoadFile(filePath.c_str());
		if (error != tinyxml2::XML_SUCCESS)
		{
			return false;
		}
		tinyxml2::XMLElement* mapElm = document_.FirstChildElement("map");
		if (mapElm->IntAttribute("width") == state_.mapSize_.x && mapElm->IntAttribute("hight") == state_.mapSize_.y)
		{
			std::string mapStr = mapElm->GetText();
			std::stringstream ss{ mapStr };
			std::string buf;
			int y = 0;
			int x = 0;
			while (std::getline(ss, buf, ','))
			{

				mapData_[y][x++] = (static_cast<MapChipName>(std::atoi(buf.c_str())));
				if (x >= state_.mapSize_.x)
				{
					y++;
					x = 0;
				}
				if (y >= state_.mapSize_.y)
				{
					break;
				}
			}
			error = document_.SaveFile(filePath.c_str());
			if (error)
			{
				return false;
			}

		}
		else
		{
			std::function<void(int&, std::list<std::string>)>check = [&](int &num,std::list<std::string>fileList) {
				char tmp[256];
				sprintf_s(tmp, "%d", num);
				auto fItr=std::find(fileList.begin(), fileList.end(), _WtS(name) + "(" + tmp + ").xml");
				if (fItr == fileList.end())
				{
					return;
				}
				else
				{
					num++;
					check(num,fileList);
				}
			};
			int num = 1;
			check(num,fileList);
			create(num);
		}

	}


	return true;
}

bool Custom::SaveFile()
{
	std::string mapData="\n";
	for (auto data1 : mapData_)
	{
		for (auto data2 : data1)
		{
			mapData += std::to_string(static_cast<char>(data2));
			mapData += ",";
		}
		mapData += "\n";
	}
	
	std::string filePath = "data/mapData/" + _WtS(state_.name_) + (state_.name_.find(L".xml") != state_.name_.npos ? "" : ".xml");
	auto error=document_.LoadFile(filePath.c_str());
	if (error != tinyxml2::XML_SUCCESS)
	{
		return false;
	}
	auto elm = document_.FirstChildElement("map");
	elm->SetText(mapData.c_str());
	elm->SetAttribute("hight", mapData_.size());
	elm->SetAttribute("width", mapData_[0].size());
	error=document_.SaveFile(filePath.c_str());
	if (error != tinyxml2::XML_SUCCESS)
	{
		return false;
	}
	return true;
}

const VECTOR2& Custom::GetMainStay()
{
	return mainStay_;
}

const std::map<int, VECTOR2>& Custom::Getspawner()
{
	return spawners_;
}

