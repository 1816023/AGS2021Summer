#include "ScrollList.h"

ScrollList::ScrollList(VECTOR2 pos, ListType type)
{
    scrollPos_ = 0;
    pos_ = pos;
    type_ = type;
}

ScrollList::~ScrollList()
{
}

bool ScrollList::Add(std::string str)
{
    return false;
}

bool ScrollList::Add(int handle)
{
    return false;
}

bool ScrollList::Add(BoxState state)
{
    return false;
}

void ScrollList::Update()
{
}

void ScrollList::Draw()
{
}
