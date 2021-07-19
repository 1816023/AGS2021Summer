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
	Custom(VECTOR2 offset);
	~Custom()override;
	void SetUp(std::wstring fileName, VECTOR2 fileSize);
	bool SetChip(VECTOR2 pos, MapChipName chip);
	bool SetChipByIdx(VECTOR2 idx, MapChipName chip);
	bool CreateMapFile(VECTOR2 mapSize, std::wstring name);
	bool SaveFile();
	bool SaveFile(int spawnerNum,const std::vector<std::vector<std::pair<std::unique_ptr<ImgeAndStringList>, std::vector<int>>>>&list);
	void FindMapObj(mapChipVec& map, const int& y, mapChipVec::iterator fStart);
	const std::vector<int>& GetMainStay();
	const std::vector<int>& GetSpawner();
	VECTOR2 PosFromIndex(int index);
private:
	// インデックスを格納
	// ※インデックスはx+y*xの最大
	// 拠点座標
	std::vector<int> mainStay_;
	// 敵出現位置の座標
	std::vector<int>spawners_;
	// 描画のオフセット
	VECTOR2 offset_;
	int mapIdx;
};

