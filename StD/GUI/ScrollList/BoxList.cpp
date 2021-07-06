#include <DxLib.h>
#include "BoxList.h"
#include "../../MouseController.h"
BoxList::BoxList(VECTOR2 pos, VECTOR2 size):ScrollList(pos,size)
{
    type_ = ListType::COLOR_BOX;
}

BoxList::~BoxList()
{
}

bool BoxList::Add(BoxState state)
{
    if (type_ != ListType::COLOR_BOX)
    {
        return false;
    }
    list_.emplace_back(state);
    return true;
}

bool BoxList::Del()
{
    auto error = list_.erase(list_.end());
    return error != list_.end();
}

void BoxList::Update()
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

void BoxList::Draw()
{
    auto defScreen = GetDrawScreen();
    SetDrawScreen(screen_);
    ClearDrawScreen();
    // Ç±Ç±Ç…èàóù------------



    // --------------------
    DrawBox(0, 0, size_.x, size_.y, 0xffffff, false);
    SetDrawScreen(defScreen);
    DrawGraph(pos_.x, pos_.y, screen_, true);

}
