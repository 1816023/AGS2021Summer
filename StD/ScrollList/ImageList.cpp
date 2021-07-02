#include <DxLib.h>
#include "ImageList.h"
#include "../MouseController.h"

ImageList::ImageList(VECTOR2 pos, VECTOR2 size):ScrollList(pos,size)
{
    type_ = ListType::IMAGE;
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
    int x, y;
    GetGraphSize(handle, &x, &y);
    list_.emplace_back(ImageState{handle,VECTOR2(x,y)});
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
        int size = 0;
        for (auto list : list_)
        {
            size += list.size.y;
        }
        scrollPos_ = (scrollPos_ >=  -size ? scrollPos_ : -size);

    }

}

void ImageList::Draw()
{
    auto defScreen = GetDrawScreen();
    SetDrawScreen(screen_);
    ClearDrawScreen();
    // Ç±Ç±Ç…èàóù------------
    int cnt = 0;

    for (auto list : list_)
    {
        DrawGraph(1,1+list.size.y*cnt+scrollPos_ , list.handle, true);

        cnt++;
    }



    // --------------------

    DrawBox(0, 0, size_.x, size_.y, 0xffffff, false);
    SetDrawScreen(defScreen);
    DrawGraph(pos_.x, pos_.y, screen_, true);

}
