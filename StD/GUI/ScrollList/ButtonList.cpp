#include "ButtonList.h"
#include <DxLib.h>
#include "../../MouseController.h"
ButtonList::ButtonList(VECTOR2 pos, VECTOR2 size):ScrollList(pos,size)
{
	type_ = ListType::BUTTON;

}

ButtonList::~ButtonList()
{
}

bool ButtonList::Add(int color, std::function<bool()> func)
{
	if (type_ != ListType::BUTTON)
	{
		return false;
	}
	const int size = GetFontSize();
	list_.emplace_back(std::make_unique<RectButton>(VECTOR2(0, list_.size() * size), VECTOR2(size_.x, size + size * list_.size()), color, func, VECTOR2()));

	return true;
}

bool ButtonList::Del()
{
	auto error = list_.erase(list_.end());
	return error!=list_.end();
}

void ButtonList::Update()
{
	lpMouseController.GetWheel();
	if (lpMouseController.IsHitBoxToMouse(pos_, pos_ + size_))
	{
		//scrollPos_ = 0;
		scrollPos_ += lpMouseController.GetWheel();
		scrollPos_ = (scrollPos_ <= 0.0f ? scrollPos_ : 0.0f);
		int size = list_.size();
		scrollPos_ = (scrollPos_ >= -GetFontSize() * size ? scrollPos_ : -GetFontSize() * size);
		
		auto pos = lpMouseController.GetPos();
		pos = VECTOR2(pos.x, pos.y - scrollPos_);
		for (auto&& list : list_)
		{
			if (list->IsHit(pos))
			{
				list->PushFunction();
			}
		}
	}

}

void ButtonList::Draw()
{
	auto defScreen = GetDrawScreen();
	SetDrawScreen(screen_);
	ClearDrawScreen();

	for (auto&& list : list_)
	{
		list->Draw();
	}

	DrawBox(0, 0, size_.x, size_.y, 0xffffff, false);
	SetDrawScreen(defScreen);
	DrawGraph(pos_.x, pos_.y, screen_, true);

}
