#pragma once
#include "Map.h"
#include <map>
#include <memory>
#define MAX_MAP_SIZE 20
#define MIN_MAP_SIZE 10
using mapChipVec = std::vector<MapChipName>;

// マップ情報の編集用クラス
enum class ErrorCode : int;
class Custom :
	public Map
{
public:
	Custom(VECTOR2 offset);
	~Custom()override;
	void SetUp(std::wstring fileName, VECTOR2 fileSize);
	bool SetChip(VECTOR2 pos, MapChipName chip);
	bool CreateMapFile(VECTOR2 mapSize,std::wstring name);
	bool SaveFile();
	void FindMainStay(mapChipVec& map,const int& y, mapChipVec::iterator fStart);
	const std::vector<int>& GetMainStay();
	const std::vector<int>& GetSpawner();
	VECTOR2 PosFromIndex(int index);
private:
	// インデックスを格納
	// ※インデックスはx+y*xの最大
	std::vector<int> mainStay_;	
	// 敵出現位置の座標
	std::vector<int>spawners_;
	// 描画のオフセット
	VECTOR2 offset_;
	int mapIdx;
};

