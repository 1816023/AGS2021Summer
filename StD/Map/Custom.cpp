#include "Custom.h"
#include <fstream>
#include <Windows.h>
#include <functional>
#include <sstream>
#include <cassert>
#include "../File/FileSystem.h"
#include "../StringUtil.h"
#include "../Application.h"
#include "../MapEnum.h"

Custom::Custom(VECTOR2 offset) :offset_(offset)
{
	mapIdx = 0;
}

Custom::~Custom()
{
}

void Custom::SetUp(std::wstring fileName, VECTOR2 mapSize)
{
	state_.name_ = fileName;
	if (fileName.find(L".xml") == fileName.npos)
	{
		state_.name_ += L".xml";
	}
	state_.mapSize_ = mapSize;
	state_.chipSize_ = { 64,64 };
	mapData_.clear();
	mapData_.resize(mapSize.y);

	if (!Map::SetUp(StringUtil::WStringToString(fileName)))
	{
		// マップが存在しない時
		mapData_.resize(mapSize.y);
		for (auto& map : mapData_)
		{
			while (map.size() < state_.mapSize_.x)
			{
				map.push_back(MapChipName::WALL);
			}
		}
	}
	else
	{
		// マップが存在した時
		int y = 0;
		// 自拠点を検索して格納する
		for (auto map : mapData_)
		{
			// 再起
			FindMapObj(map, y, map.begin());
			y++;
		}
		// セーブされたスポナーを読み込み
	}
	CreateMapFile(mapSize, fileName);
}

bool Custom::SetChip(VECTOR2 pos, MapChipName chip)
{
	VECTOR2 mapPos = pos / state_.chipSize_;
	return SetChipByIdx(mapPos, chip);
}

bool Custom::SetChipByIdx(VECTOR2 idx, MapChipName chip)
{
	if (0 > idx.x || idx.x > state_.mapSize_.x)
	{
		return false;
	}
	if (0 > idx.y || idx.y > state_.mapSize_.y)
	{
		return false;
	}
	if (idx.x > state_.mapSize_.x || idx.y > state_.mapSize_.y)
	{
		return false;
	}
	int id = idx.x + idx.y * state_.mapSize_.x;
	auto msFind = std::find(mainStay_.begin(), mainStay_.end(), id);
	auto spFind = std::find(spawners_.begin(), spawners_.end(), id);
	if (chip == MapChipName::MAINSTAY)
	{
		if (mainStay_.size() < 2 && msFind == mainStay_.end())
		{
			mainStay_.emplace_back(id);
			mapData_[idx.y][idx.x] = chip;
		}
	}
	else if (chip == MapChipName::SPAWNER)
	{
		if (spFind == spawners_.end() && spawners_.size() < 2)
		{
			spawners_.emplace_back(id);
			mapData_[idx.y][idx.x] = chip;
			return true;
		}
	}
	else
	{
		if (msFind != mainStay_.end())
		{
			mainStay_.erase(msFind);
		}
		if (spFind != spawners_.end())
		{
			spawners_.erase(spFind);
		}
		mapData_[idx.y][idx.x] = chip != MapChipName::MAX ? chip : mapData_[idx.y][idx.x];
	}
	return true;
}

bool Custom::CreateMapFile(VECTOR2 mapSize, std::wstring name)
{
	std::list<std::string>fileList;
	FileSystem::serch("data/mapData", fileList);
	if (name.find(L".xml") == name.npos)
	{
		name += L".xml";
	}
	auto itr = std::find(fileList.begin(), fileList.end(), _WtS(name));
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
			filePath = "data/mapData/" + _WtS(name) + "(" + tmp + ")" + ".xml";

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
		int idx = 0;
		for (auto& y : mapData_)
		{
			
			for (auto& data : y)
			{
				mapData += std::to_string(static_cast<char>(data));
				idx++;
				if (idx < mapSize.x * mapSize.y)
				{
					mapData += ",";
				}
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
			std::function<void(int&, std::list<std::string>)>check = [&](int& num, std::list<std::string>fileList) {
				char tmp[256];
				sprintf_s(tmp, "%d", num);
				auto fItr = std::find(fileList.begin(), fileList.end(), _WtS(name) + "(" + tmp + ").xml");
				if (fItr == fileList.end())
				{
					return;
				}
				else
				{
					num++;
					check(num, fileList);
				}
			};
			int num = 1;
			check(num, fileList);
			create(num);
		}

	}
	return true;
}

bool Custom::SaveFile()
{
	std::string mapData = "\n";
	int idx = 0;
	for (auto& data1 : mapData_)
	{
		for (auto& data2 : data1)
		{
			idx++;
			mapData += std::to_string(static_cast<char>(data2));
			if (idx != data1.size() * mapData_.size())
			{
				mapData += ",";
			}
		}
		mapData += "\n";
	}

	std::string filePath = "data/mapData/" + _WtS(state_.name_) + (state_.name_.find(L".xml") != state_.name_.npos ? "" : ".xml");
	auto error = document_.LoadFile(filePath.c_str());
	if (error != tinyxml2::XML_SUCCESS)
	{
		return false;
	}
	auto elm = document_.FirstChildElement("map");
	elm->SetText(mapData.c_str());
	elm->SetAttribute("hight", mapData_.size());
	elm->SetAttribute("width", mapData_[0].size());
	error = document_.SaveFile(filePath.c_str());
	if (error != tinyxml2::XML_SUCCESS)
	{
		return false;
	}
	return true;
}

void Custom::FindMapObj(mapChipVec& map, const int& y, mapChipVec::iterator fStart)
{
	auto find = std::find_if(fStart, map.end(), [](const MapChipName& data)
		{
			return data == MapChipName::MAINSTAY || data == MapChipName::SPAWNER;
		});

	if (find != map.end())
	{
		if (*find == MapChipName::MAINSTAY)
		{
			// 拠点数限界以上のデータだった場合
			// ※マップデータ外部でいじる時注意
			if (mainStay_.size() > 2)
			{
				assert(false);
			}
			auto point = VECTOR2(static_cast<int>(std::distance(map.begin(), find)), y);
			mainStay_.emplace_back(point.x + point.y * state_.mapSize_.x);

			
		}
		if (*find == MapChipName::SPAWNER)
		{
			// スポナー数限界以上のデータだった場合
			// ※スポナーデータ外部でいじる時注意
			if (spawners_.size() > 2)
			{
				assert(false);
			}
			auto point = VECTOR2(static_cast<int>(std::distance(map.begin(), find)), y);
			spawners_.emplace_back(point.x + point.y * state_.mapSize_.x);
		}
		// 再帰的に次を返す
		FindMapObj(map, y, find + 1);
	}
}

const std::vector<int>& Custom::GetMainStay()
{
	return mainStay_;
}

const std::vector<int>& Custom::GetSpawner()
{
	return spawners_;
}

VECTOR2 Custom::PosFromIndex(int index)
{
	auto y = index / state_.mapSize_.x;
	return VECTOR2(index - y * state_.mapSize_.x, y);
}