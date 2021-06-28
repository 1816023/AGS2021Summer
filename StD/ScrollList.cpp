#include "ScrollList.h"
#include <DxLib.h>
#include "MouseController.h"
#include "StringUtil.h"

ScrollList::ScrollList(VECTOR2 pos,VECTOR2 size, ListType type, int fonthande)
{
    scrollPos_ = 0;
    pos_ = pos;
    size_ = size;
    type_ = type;
    fontH_ =fonthande;
    screen_ = MakeScreen(size_.x, size_.y,0);
}

ScrollList::~ScrollList()
{
}

bool ScrollList::Add(StringState state)
{
    if (type_ != ListType::STRING)
    {
        return false;
    }
    slist_.emplace_back(state);
    return true;
}

bool ScrollList::Add(int handle)
{
    if (type_ != ListType::IMAGE)
    {
        return false;
    }
    ilist_.emplace_back(handle);
    return true;
}

bool ScrollList::Add(BoxState state)
{
    if (type_ != ListType::COLOR_BOX)
    {
        return false;
    }
    blist_.emplace_back(state);
    return true;
}

void ScrollList::Update()
{
    lpMouseController.GetWheel();
    if (lpMouseController.IsHitBoxToMouse(pos_,pos_+size_))
    {
        scrollPos_ = 0;
        scrollPos_ += lpMouseController.GetWheel();
    }
}

void ScrollList::Draw()
{
    auto defScreen = GetDrawScreen();
    SetDrawScreen(screen_);
    ClearDrawScreen();
    switch (type_)
    {
    case ListType::STRING:
        sDraw();
        break;
    case ListType::IMAGE:
        iDraw();
        break;
    case ListType::COLOR_BOX:
        bDraw();
        break;
    case ListType::Max:
        break;
    default:
        break;
    }
    SetDrawScreen(defScreen);
    DrawGraph(pos_.x, pos_.y, screen_, true);
}

void ScrollList::sDraw()
{
    int cnt = 0;
    int fontsize = (fontH_ == -1 ?GetFontSize():GetFontSizeToHandle(fontH_));
    
    for (auto list : slist_)
    {
        if (fontH_ ==-1)
        {
            DrawString(0, fontsize*cnt+scrollPos_, _StW("ÅE"+list.str).c_str(), list.color);
        }
        else
        {
            DrawStringToHandle(0, fontsize*cnt+scrollPos_, _StW("ÅE"+list.str).c_str(), list.color, fontH_);
        }
        cnt++;
    }
}

void ScrollList::iDraw()
{
}

void ScrollList::bDraw()
{
}
