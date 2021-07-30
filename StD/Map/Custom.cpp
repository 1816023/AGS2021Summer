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
#include "../GUI/ScrollList/ImgeAndStringList.h"
#include "../Unit/Enemy/Enemy.h"
#include "../Mng/ImageMng.h"
Custom::Custom(VECTOR2 offset) :offset_(offset)
{
	mapIdx = 0;
}

Custom::~Custom()
{
}

void Custom::SetUp(std::wstring fileName, VECTOR2 mapSize)
{
	mainStay_.clear();
	mainStay_.shrink_to_fit();
	spawners_.clear();
	spawners_.shrink_to_fit();
	state_.name_ = fileName;
	if (fileName.find(L".xml") == fileName.npos)
	{
		state_.name_ += L".xml";
	}
	state_.mapSize = mapSize;
	state_.chipSize = { 64,64 };
	mapData_.clear();
	mapData_.resize(mapSize.y);

	if (!Map::SetUp(StringUtil::WStringToString(fileName)))
	{
		// �}�b�v�����݂��Ȃ���
		mapData_.resize(mapSize.y);
		for (auto& map : mapData_)
		{
			while (map.size() < state_.mapSize.x)
			{
				map.push_back(MapChipName::WALL);
			}
		}
	}
	else
	{
		// �}�b�v�����݂�����
		int y = 0;
		// �����_���������Ċi�[����
		for (auto& map : mapData_)
		{
			// �ċN
			FindMapObj(map, y, map.begin());
			y++;
		}
		// �Z�[�u���ꂽ�X�|�i�[��ǂݍ���
	}
	CreateMapFile(mapSize, fileName);
}

bool Custom::SetChip(VECTOR2 pos, MapChipName chip)
{
	VECTOR2 mapPos = pos / state_.chipSize;
	return SetChipByIdx(mapPos, chip);
}

bool Custom::SetChipByIdx(VECTOR2 idx, MapChipName chip)
{
	if (chip == MapChipName::MAX)
	{
		return false;
	}
	if (0 > idx.x || idx.x > state_.mapSize.x)
	{
		return false;
	}
	if (0 > idx.y || idx.y > state_.mapSize.y)
	{
		return false;
	}
	if (idx.x >= state_.mapSize.x || idx.y >= state_.mapSize.y)
	{
		return false;
	}
	int id = idx.x + idx.y * state_.mapSize.x;
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
		if (mapElm->IntAttribute("width") == state_.mapSize.x && mapElm->IntAttribute("hight") == state_.mapSize.y)
		{
			std::string mapStr = mapElm->GetText();
			std::stringstream ss{ mapStr };
			std::string buf;
			int y = 0;
			int x = 0;
			while (std::getline(ss, buf, ','))
			{

				mapData_[y][x++] = (static_cast<MapChipName>(std::atoi(buf.c_str())));
				if (x >= state_.mapSize.x)
				{
					y++;
					x = 0;
				}
				if (y >= state_.mapSize.y)
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

bool Custom::SaveFile(int spawnerNum,const std::vector<std::vector<std::pair<std::unique_ptr<ImgeAndStringList>, std::vector<int>>>> &list)
{
	//���̌`�ŕۑ�
	// <wave id = "">
	//	<spawner id = "">
	//		<enemy type = "" time = "" root = "" / >
	//		<enemy type = "" time = "" root = "" / >
	//	</spawner>
	// </wave>
	using namespace tinyxml2;
	std::string filePath = "data/mapData/" + _WtS(state_.name_) + (state_.name_.find(L".xml") != state_.name_.npos ? "" : ".xml");

	auto error = document_.LoadFile(filePath.c_str());
	if (error != XML_SUCCESS)
	{
		// �t�@�C���I�[�v���G���[
		return 1;
	}
	tinyxml2::XMLElement* elm = document_.FirstChildElement("spawn");
	// �w�肵���G�������g��"id"�A�g���r���[�g���w�肳�ꂽ���̂ɂȂ�܂ŌZ���T���ɍs��
	// �T���o�����true�@
	// ������Ȃ�������false
	std::function<tinyxml2::XMLElement*(tinyxml2::XMLElement*, int)> check = [&](tinyxml2::XMLElement* elm, int num) {
		if (elm->IntAttribute("id") != num)
		{
			auto tmp = elm->NextSiblingElement(elm->Name());
			if (!tmp)
			{
				return tmp;
			}
			
			return check(tmp, num);
		}

		return elm;
	};
	std::map<int, EnemyType>enemyID = {
		{IMAGE_ID(L"./data/image/circle.png"),EnemyType::Circle},
		{IMAGE_ID(L"./data/image/square.png"),EnemyType::Square},
		{IMAGE_ID(L"./data/image/pentagon.png"),EnemyType::Pentagon},
		{IMAGE_ID(L"./data/image/triangle.png"),EnemyType::Triangle},

	};
	/////
	// �E�F�[�u�̐���
	for (int w = 0; w < 3; w++)
	{
		// �h�L�������g����wave�̃G�������g���擾����
		tinyxml2::XMLElement* wave = elm->FirstChildElement("wave");
		if (!wave)
		{
			document_.SaveFile(filePath.c_str());
			return 1;
		}
		// �擾�����G�������g���w�肵��ID�������̂ɂȂ�܂ōċA����
		wave = check(wave, w + 1);
		if (wave)
		{
			// ���Ƃ��Ƃ���f�[�^��S������
			wave->DeleteChildren();
			// �X�|�i�[�̐�������
			for (int s = 0; s < spawnerNum; s++)
			{
				// ���X�g�̎擾
				auto& enemyList = list[w][s].first->GetList();
				// �X�|�i�[�̃G�������g�쐬
				tinyxml2::XMLElement* spawner = wave->InsertNewChildElement("spawner");
				if (!spawner)
				{
					// �V�K�G�������g�G���[
					return 2;
				}
				// �X�|�i�[��ID��ݒ�
				spawner->SetAttribute("id", s);
				int cnt = 0;
				// ���X�g�̂Ł[�������ƂɃX�|�i�[�G�������g�ɒǉ����Ă���
				for (auto& elist : enemyList)
				{
					// �V����enemy�Ƃ����G�������g���쐬����
					tinyxml2::XMLElement* element = document_.NewElement("enemy");
					// �X�|�i�[�̎q���̌��ɍ쐬����enemy�G�������g��ǉ�����
					spawner->InsertEndChild(element);
					// �G�l�~�[��type,time,root�̃A�g���r���[�g��ǉ�����
					element->SetAttribute("type", static_cast<int>(enemyID[elist.handle]));
					element->SetAttribute("time", elist.str.c_str());
					element->SetAttribute("root", list[w][s].second[cnt++]);
				}
			}
		}

	}
	document_.SaveFile(filePath.c_str());
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
			// ���_�����E�ȏ�̃f�[�^�������ꍇ
			// ���}�b�v�f�[�^�O���ł����鎞����
			if (mainStay_.size() > 2)
			{
				assert(false);
			}
			auto point = VECTOR2(static_cast<int>(std::distance(map.begin(), find)), y);
			mainStay_.emplace_back(point.x + point.y * state_.mapSize.x);

			
		}
		if (*find == MapChipName::SPAWNER)
		{
			// �X�|�i�[�����E�ȏ�̃f�[�^�������ꍇ
			// ���X�|�i�[�f�[�^�O���ł����鎞����
			if (spawners_.size() > 2)
			{
				assert(false);
			}
			auto point = VECTOR2(static_cast<int>(std::distance(map.begin(), find)), y);
			spawners_.emplace_back(point.x + point.y * state_.mapSize.x);
		}
		// �ċA�I�Ɏ���Ԃ�
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
	auto y = index / state_.mapSize.x;
	return VECTOR2(index - y * state_.mapSize.x, y);
}