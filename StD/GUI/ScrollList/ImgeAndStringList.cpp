#include "ImgeAndStringList.h"
#include <DxLib.h>
#include "../../MouseController.h"
#include "../../StringUtil.h"
ImgeAndStringList::ImgeAndStringList(VECTOR2 pos, VECTOR2 size):ScrollList(pos,size)
{
	type_ = ListType::ImageAndString;
}

ImgeAndStringList::~ImgeAndStringList()
{
}

bool ImgeAndStringList::Add(int handle,std::string str)
{
    if (type_ != ListType::ImageAndString)
    {
        return false;
    }
    int x, y;
    GetGraphSize(handle, &x, &y);
    list_.emplace_back(IandSState{ handle,VECTOR2(x,y),str });
    return true;
}

bool ImgeAndStringList::Del()
{
    if (list_.size() != 0)
    {
        list_.pop_back();
        return true;
    }
    return false;
}

void ImgeAndStringList::Update()
{
    lpMouseController.GetWheel();
    if (lpMouseController.IsHitBoxToMouse(pos_, pos_ + size_))
    {
        //scrollPos_ = 0;
        scrollPos_ += lpMouseController.GetWheel()*3;
        scrollPos_ = (scrollPos_ <= 0.0f ? scrollPos_ : 0.0f);
        int size = 0;
        for (auto list : list_)
        {
            size += list.size.y;
        }
        scrollPos_ = (scrollPos_ >= -size ? scrollPos_ : -size);

    }

}

void ImgeAndStringList::Draw()
{
    auto defScreen = GetDrawScreen();
    SetDrawScreen(screen_);
    ClearDrawScreen();
    // Ç±Ç±Ç…èàóù------------
    int cnt = 0;
    if (list_.size() != 0)
    {
        for (auto list : list_)
        {
            DrawGraph(1, 1 + list.size.y * cnt + scrollPos_, list.handle, true);
            DrawString(list.size.x + 5, (list.size.y/2-GetFontSize()/2)+ list.size.y * cnt + scrollPos_, _StW(list.str).c_str(), 0xffffff);
            cnt++;
        }

    }



    // --------------------

    DrawBox(0, 0, size_.x, size_.y, 0xffffff, false);
    SetDrawScreen(defScreen);
    DrawGraph(pos_.x, pos_.y, screen_, true);

}
