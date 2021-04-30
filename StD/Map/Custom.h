#pragma once
#include "Map.h"
#define MAX_MAP_SIZE 20
#define MIN_MAP_SIZE 10
// マップ情報の編集用クラス
class Custom :
	public Map
{
public:
	Custom(VECTOR2 offset);
	~Custom()override;
	void SetUp(std::wstring fileName, VECTOR2 fileSize);
	// 
	bool SetChip(VECTOR2 pos, MapChipName chip);
	bool CreateMapFile(VECTOR2 mapSize,std::wstring name);
	bool SaveFile();
private:
	// 描画のオフセット
	VECTOR2 offset_;
};

