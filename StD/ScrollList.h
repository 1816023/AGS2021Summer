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
class ScrollList
{
public:
	ScrollList(VECTOR2 pos,ListType type);
	~ScrollList();
	// string�^�̗v�f�ǉ�
	bool Add(std::string str);
	// �摜�^�̗v�f�ǉ�
	bool Add(int handle);
	// �F�����Ƃ̗v�f�ǉ�
	bool Add(BoxState state);
	
	void Update();
	void Draw();
private:
	int scrollPos_;
	VECTOR2 pos_;
	ListType type_;
	std::list<std::string>slist_;
	std::list<int>ilist_;
	std::list<BoxState>blist_;
};

