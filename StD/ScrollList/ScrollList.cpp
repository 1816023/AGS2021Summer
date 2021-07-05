#include "ScrollList.h"
#include <DxLib.h>

ScrollList::ScrollList(VECTOR2 pos,VECTOR2 size)
{
    scrollPos_ = 0;
    pos_ = pos;
    size_ = size;
    screen_ = MakeScreen(size_.x, size_.y,1);
}

ScrollList::~ScrollList()
{
}


