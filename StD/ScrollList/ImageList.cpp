#include <DxLib.h>
#include "ImageList.h"
#include "../MouseController.h"

ImageList::ImageList(VECTOR2 pos, VECTOR2 size, ListType type):ScrollList(pos,size,type)
{
}

ImageList::~ImageList()
{
}

bool ImageList::Add(int handle)
{
    if (type_ != ListType::IMAGE)
    {
        return false;
    }
    list_.emplace_back(handle);
    return true;
}

bool ImageList::Del()
{
    auto error = list_.erase(list_.end());
    return error != list_.end();
}

void ImageList::Update()
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

void ImageList::Draw()
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
