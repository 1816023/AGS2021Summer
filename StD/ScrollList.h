#pragma once
#include <list>
#include <array>
#include <string>
enum class ListType
{
	STRING,
	BUTTOM,
	IMAGE,
	COLOR_BOX,
	Max
};
class ScrollList
{
public:
	

private:
	ListType type_;
	std::list<std::string>slist_;
};

