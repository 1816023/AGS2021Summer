#include "ScrollList.h"
#include <DxLib.h>

ScrollList::ScrollList(VECTOR2 pos,VECTOR2 size, ListType type)
{
    scrollPos_ = 0;
    pos_ = pos;
    size_ = size;
    type_ = type;
    screen_ = MakeScreen(size_.x, size_.y,1);
}

ScrollList::~ScrollList()
{
}


