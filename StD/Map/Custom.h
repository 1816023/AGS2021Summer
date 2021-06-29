#pragma once
#include "Map.h"
#include <map>
#include <memory>
#define MAX_MAP_SIZE 20
#define MIN_MAP_SIZE 10
using mapChipVec = std::vector<MapChipName>;

// �}�b�v���̕ҏW�p�N���X
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
	// �C���f�b�N�X���i�[
	// ���C���f�b�N�X��x+y*x�̍ő�
	std::vector<int> mainStay_;	
	// �G�o���ʒu�̍��W
	std::vector<int>spawners_;
	// �`��̃I�t�Z�b�g
	VECTOR2 offset_;
	int mapIdx;
};

