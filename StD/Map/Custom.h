#pragma once
#include "Map.h"
#define MAX_MAP_SIZE 20
#define MIN_MAP_SIZE 10
// �}�b�v���̕ҏW�p�N���X
class Custom :
	public Map
{
public:
	Custom();
	~Custom()override;
	void SetUp(std::wstring fileName, VECTOR2 fileSize);
	// 
	bool SetChip(VECTOR2 pos, MapChipName chip);
private:
	
};

