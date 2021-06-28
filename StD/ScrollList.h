#pragma once
#include <list>
#include <array>
#include <string>
#include <memory>
#include "./VECTOR2.h"
enum class ListType
{
	STRING,
	IMAGE,
	COLOR_BOX,
	Max
};

struct BoxState
{
	VECTOR2 size;
	int color;
};
struct StringState 
{
	std::string str;
	int color;
};
class ScrollList
{
public:
	
	ScrollList(VECTOR2 pos,VECTOR2 size,ListType type,int fonthande=-1);
	~ScrollList();
	// string�^�̗v�f�ǉ�
	// ���g�Ɠ����^�C�v����Ȃ��ꍇfalse��Ԃ�
	bool Add(StringState state);
	// �摜�^�̗v�f�ǉ�
	// ���g�Ɠ����^�C�v����Ȃ��ꍇfalse��Ԃ�
	bool Add(int handle);
	// �F�����Ƃ̗v�f�ǉ�
	// ���g�Ɠ����^�C�v����Ȃ��ꍇfalse��Ԃ�
	bool Add(BoxState state);
	
	void Update();
	void Draw();
private:
	// �X�N���[����
	int scrollPos_;
	// �`��ʒu�i����j
	VECTOR2 pos_;
	// �`��T�C�Y
	VECTOR2 size_;
	// ���X�g�^�C�v
	ListType type_;
	// string�^�p�̃��X�g
	std::list<StringState>slist_;
	// �摜�^�p�̃��X�g
	std::list<int>ilist_;
	// �F���^�̃��X�g
	std::list<BoxState>blist_;
	// �`��X�N���[��
	int screen_;
	// string�^�d�l�p�̃t�H���g�n���h��
	int fontH_;

	void sDraw();
	void iDraw();
	void bDraw();
};

