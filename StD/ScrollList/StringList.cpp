#include <DxLib.h>
#include "StringList.h"
#include "../MouseController.h"
#include "../StringUtil.h"

StringList::StringList(VECTOR2 pos, VECTOR2 size, int fonthande):ScrollList(pos,size)
{
    type_ = ListType::STRING;
    fontH_ = fonthande;
}

StringList::~StringList()
{
    DeleteFontToHandle(fontH_);
}

bool StringList::Add(StringState state)
{
    if (type_ != ListType::STRING)
    {
        return false;
    }
    list_.emplace_back(state);
    return true;
}

bool StringList::Del()
{
    auto error = list_.erase(list_.end());
	return error!=list_.end();
}

void StringList::Update()
{
    lpMouseController.GetWheel();
    if (lpMouseController.IsHitBoxToMouse(pos_, pos_ + size_))
    {
        //scrollPos_ = 0;
        scrollPos_ += lpMouseController.GetWheel();
        scrollPos_ = (scrollPos_ <= 0.0f ? scrollPos_ : 0.0f);
        int size = list_.size();
        scrollPos_ = (scrollPos_ >= -GetFontSize() * size ? scrollPos_ : -GetFontSize() * size);

    }

}

void StringList::Draw()
{
    auto defScreen = GetDrawScreen();
    SetDrawScreen(screen_);
    ClearDrawScreen();
    // Ç±Ç±Ç…èàóù------------

    int cnt = 0;
    int fontsize = (fontH_ == -1 ? GetFontSize() : GetFontSizeToHandle(fontH_));

    for (auto list : list_)
    {
        if (fontH_ == -1)
        {
            DrawString(1, 1 + fontsize * cnt + scrollPos_, _StW("ÅE" + list.str).c_str(), list.color);
        }
        else
        {
            DrawStringToHandle(1, 1 + fontsize * cnt + scrollPos_, _StW("ÅE" + list.str).c_str(), list.color, fontH_);
        }
        cnt++;
    }
    // --------------------

    DrawBox(0, 0, size_.x, size_.y, 0xffffff, false);
    SetDrawScreen(defScreen);
    DrawGraph(pos_.x, pos_.y, screen_, true);

}
