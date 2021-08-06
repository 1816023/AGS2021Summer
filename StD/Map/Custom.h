#pragma once
#include "Map.h"
#include <map>
#include <memory>
#include <functional>
using mapChipVec = std::vector<MapChipName>;

// マップ情報の編集用クラス
enum class ErrorCode : int;
class ImgeAndStringList;
class Custom :
	public Map
{
public:
	Custom();
	~Custom()override;
	void SetUp(std::wstring fileName, VECTOR2 fileSize);
	bool SetChip(VECTOR2 pos, MapChipName chip);
	bool SetChipByIdx(VECTOR2 idx, MapChipName chip);
	bool CreateMapFile(VECTOR2 mapSize, std::wstring name);
	bool SaveFile();
	bool SaveFile(int spawnerNum,const std::vector<std::vector<std::pair<std::unique_ptr<ImgeAndStringList>, std::vector<int>>>>&list);
private:
	int mapIdx_;
};

