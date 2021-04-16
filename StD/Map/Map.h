#pragma once
#include "../VECTOR2.h"
#include <string>
#include <vector>
#include "../tinyxml2/tinyxml2.h"

enum class MapChipName:char
{

	MAINSTAY=1,		// �h�q���_
	SPAWNER,		// �G�o���ʒu
	ROOT,			// �G�N�U���[�g
	FIELD,			// ���@�z�u�\�ӏ�
	WALL,			// ���@�z�u�s�\�ӏ�
	MAX

};
using dataVec = std::vector<std::vector<MapChipName>> ;
class Map
{
public:
	Map();
	virtual ~Map();
	virtual int Update();
	virtual void Draw();
	virtual bool SetUp(std::string mapName);		// �}�b�v���̏������A�}�b�v�f�[�^�̖��O(�g���q�Ȃ�)���w��
	MapChipName GetMapChip(Vec2Float pos);			// �`�b�v���̎擾�A�ق����ꏊ�̃|�W�V�������w��(float)	
	MapChipName GetMapChip(VECTOR2 pos);			// �`�b�v���̎擾�A�ق����ꏊ�̃|�W�V�������w��(int)
	VECTOR2 GetMapSize();							// �}�b�v�T�C�Y�擾
	VECTOR2 GetChipSize();							// �`�b�v�T�C�Y�擾	
protected:
	bool LoadMap(std::string mapName);				// �}�b�v�����[�h����A�}�b�v�f�[�^�̖��O(�g���q�Ȃ�)���w��
	VECTOR2 mapSize_;								// �}�b�v��chip��
	VECTOR2 chipSize_;								// 1chip�̃T�C�Y
	dataVec mapData_;								// �}�b�v�f�[�^�̊i�[2�����z��
	tinyxml2::XMLDocument document;					// �}�b�v�f�[�^��XML�t�@�C�������[�h�����f�[�^
};


