#pragma once
#include "../VECTOR2.h"
#include <string>
#include <vector>
#include "../tinyxml2/tinyxml2.h"
#include "../Unit/Enemy/EnemyType.h"


// �`�b�v���̖��O
enum class MapChipName:unsigned int
{

	MAINSTAY=1,		// �h�q���_				��
	SPAWNER,		// �G�o���ʒu			��
	ROOT,			// �G�N�U���[�g			��
	FIELD,			// ���@�z�u�\�ӏ�		�D/��
	WALL,			// ���@�z�u�s�\�ӏ�	���i�w�i�F�j
	MAX

};
using mapChipVec = std::vector<MapChipName>;

// 
struct MapState
{
	VECTOR2 mapSize;
	VECTOR2 chipSize;
	std::wstring name_;

};
using dataVec = std::vector<std::vector<MapChipName>> ;
using rootVec = std::vector<RootDir> ;
// �}�b�v���̕\���擾�p�N���X
class Map
{
public:
	Map();
	virtual ~Map();
	virtual int Update();
	virtual void Draw();
	// �}�b�v���̏������A�}�b�v�f�[�^�̖��O(�g���q�Ȃ�)���w��
	virtual bool SetUp(std::string mapName);		
	// �`�b�v���̎擾�A�ق����ꏊ�̃|�W�V�������w��(float)	
	MapChipName GetMapChip(Vec2Float pos);			
	// �`�b�v���̎擾�A�ق����ꏊ�̃|�W�V�������w��(int)
	MapChipName GetMapChip(VECTOR2 pos);		
	// �`�b�v���̎擾�A�ق����ꏊ�̃C���f�b�N�X���w��(int)
	MapChipName GetMapChipByIndex(VECTOR2 idx);
	// �}�b�v�T�C�Y�擾
	VECTOR2 GetMapSize();							
	// �`�b�v�T�C�Y�擾	
	VECTOR2 GetChipSize();		
	void FindMapObj(mapChipVec& map, const int& y, mapChipVec::iterator fStart);
	const std::vector<int>& GetMainStay();
	const std::vector<int>& GetSpawner();
	const std::vector<rootVec>& GetRoot();
	void SetRoot(const std::vector<rootVec>& root);
	VECTOR2 PosFromIndex(int index);
protected:
	// �}�b�v�����[�h����A�}�b�v�f�[�^�̖��O(�g���q�Ȃ�)���w��
	bool LoadMap(std::string mapName);	
	// �}�b�v�̃X�e�[�^�X
	MapState state_;						
	// �}�b�v�f�[�^�̊i�[2�����z��
	dataVec mapData_;								
	// �}�b�v�f�[�^��XML�t�@�C�������[�h�����f�[�^
	tinyxml2::XMLDocument document_;
	// �C���f�b�N�X���i�[
	// ���C���f�b�N�X��x+y*x�̍ő�
	// ���_���W
	std::vector<int> mainStay_;
	// �G�o���ʒu�̍��W
	std::vector<int>spawners_;
	// ���[�g
	std::vector<rootVec>root_;
};


