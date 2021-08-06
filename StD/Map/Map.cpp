#include <DxLib.h>
#include <sstream>
#include <array>
#include "Map.h"
#include "../StringUtil.h"
#include <cassert>
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
	for (int y = 0; y < state_.mapSize.y; y++)
	{
		for (int x = 0; x < state_.mapSize.x; x++)
		{
			if (mapData_[y][x]!=MapChipName::WALL)
			{
				DrawBox(x * state_.chipSize.x , y * state_.chipSize.y , x * state_.chipSize.x  + state_.chipSize.x , y * state_.chipSize.y + state_.chipSize.y , color[static_cast<int>(mapData_[y][x]) - 1], true);
			}
#ifdef _DEBUG
			DrawFormatString(x * state_.chipSize.x , y * state_.chipSize.y , 0xffffff, (L"%d"), (static_cast<int>(mapData_[y][x])));
#endif // _DEBUG

		}
	}
	for (int x = 0; x <= state_.mapSize.x; x++)
	{
		DrawLine(x * state_.chipSize.x, 0, x * state_.chipSize.x, state_.chipSize.x * state_.mapSize.y, 0xffffff);
	}
	for (int y = 0; y <= state_.mapSize.y; y++)
	{
		DrawLine(0, y * state_.chipSize.y, state_.chipSize.x * state_.mapSize.x, y * state_.chipSize.y, 0xffffff);
	}
	
}

bool Map::SetUp(std::string mapName)
{
	if (!Map::LoadMap(mapName))
	{
		return false;
	}
	const tinyxml2::XMLElement* mapElm = document_.FirstChildElement("map");
	state_.mapSize = { mapElm->IntAttribute("hight"),mapElm->IntAttribute("width") };
	const tinyxml2::XMLElement* chipElm = document_.FirstChildElement("chip");
	state_.chipSize = { chipElm->IntAttribute("hight"), chipElm->IntAttribute("width") };
	dataVec mapData;
	mapData.resize(state_.mapSize.y);
	std::string mapStr = mapElm->GetText();
	std::stringstream ss{ mapStr };
	std::string buf;
	int y = 0;
	while (std::getline(ss, buf, ','))
	{
		mapData[y].push_back(static_cast<MapChipName>(std::atoi(buf.c_str())));
		if (mapData[y].size()>=state_.mapSize.x)
		{
			y++;
		}
	}
	mapData_ = mapData;
	y = 0;
	// 自拠点を検索して格納する
	for (auto& map : mapData_)
	{
		// 再起
		FindMapObj(map, y, map.begin());
		y++;
	}
	return true;
}

MapChipName Map::GetMapChip(Vec2Float pos)
{
	VECTOR2 vec = { static_cast<int>(pos.x) / state_.chipSize.x,static_cast<int>(pos.y) / (state_.chipSize.y) };
	if (vec.x < 0 || vec.y < 0)
	{
		return MapChipName::MAX;
	}
	if (vec.x >= state_.mapSize.x || vec.y >= state_.mapSize.y)
	{
		return MapChipName::MAX;
	}
	
	return mapData_[vec.y][vec.x];
}

MapChipName Map::GetMapChip(VECTOR2 pos)
{
	VECTOR2 vec = pos / (state_.chipSize);
	if (vec.x < 0 || vec.y < 0)
	{
		return MapChipName::MAX;
	}
	if (vec.x >= state_.mapSize.x|| vec.y >= state_.mapSize.y)
	{
		return MapChipName::MAX;
	}

	return mapData_[vec.y][vec.x];
}

MapChipName Map::GetMapChipByIndex(VECTOR2 idx)
{
	return mapData_[idx.y][idx.x];
}

VECTOR2 Map::GetMapSize()
{
	return state_.mapSize;
}

VECTOR2 Map::GetChipSize()
{
	return state_.chipSize;
}

void Map::FindMapObj(mapChipVec& map, const int& y, mapChipVec::iterator fStart)
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
			mainStay_.emplace_back(point.x + point.y * state_.mapSize.x);


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
			spawners_.emplace_back(point.x + point.y * state_.mapSize.x);
		}
		// 再帰的に次を返す
		FindMapObj(map, y, find + 1);
	}
}

bool Map::LoadMap(std::string mapName)
{
	auto path = StringUtil::SpritExtention(mapName);
	path = "./data/mapData/" + path +".xml";
	auto error = document_.LoadFile(path.c_str());
	if (error != tinyxml2::XML_ERROR_FILE_NOT_FOUND)
	{
		return true;
	}
	return false;
}

const std::vector<int>& Map::GetMainStay()
{
	return mainStay_;
}

const std::vector<int>& Map::GetSpawner()
{
	return spawners_;
}

const std::vector<rootVec>& Map::GetRoot()
{
	return root_;
}

void Map::SetRoot(const std::vector<rootVec>& root)
{
	root_ = root;
}

const tinyxml2::XMLDocument Map::GetDocument() const
{
	return &document_;
}

