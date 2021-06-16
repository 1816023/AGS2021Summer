#pragma once
#include "../VECTOR2.h"
#include <string>
#include <vector>
#include "../tinyxml2/tinyxml2.h"

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


// 
struct MapState {
	VECTOR2 mapSize_;
	VECTOR2 chipSize_;
	std::wstring name_;

};
using dataVec = std::vector<std::vector<MapChipName>> ;
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
	// �}�b�v�T�C�Y�擾
	VECTOR2 GetMapSize();							
	// �`�b�v�T�C�Y�擾	
	VECTOR2 GetChipSize();							
protected:
	// �}�b�v�����[�h����A�}�b�v�f�[�^�̖��O(�g���q�Ȃ�)���w��
	bool LoadMap(std::string mapName);	
	// �}�b�v�̃X�e�[�^�X
	MapState state_;
	//// �}�b�v��chip��
	//VECTOR2 mapSize_;								
	//// 1chip�̃T�C�Y
	//VECTOR2 chipSize_;								
	// �}�b�v�f�[�^�̊i�[2�����z��
	dataVec mapData_;								
	// �}�b�v�f�[�^��XML�t�@�C�������[�h�����f�[�^
	tinyxml2::XMLDocument document_;	
};


