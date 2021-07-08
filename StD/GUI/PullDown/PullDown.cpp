#include "PullDown.h"
#include "../../MouseController.h"
#include <DxLib.h>
PullDown::PullDown(VECTOR2 pos, int xSize)
{
	pos_=pos;
	screen_ = MakeScreen(xSize, 2560, 1);
	GetGraphSize(screen_, &size_.x, &size_.y);
	selKey_ = 0;
	list_.emplace_back(std::make_unique<RectButton>(size_ - VECTOR2(20, 20), size_, 0xf0f0f0, [&]() {return openFlag_ = ~openFlag_; }, VECTOR2()));
	list_.back()->SetString("Бе", VECTOR2());
}

PullDown::~PullDown()
{
}

bool PullDown::Add(std::string str)
{

	return false;
}

void PullDown::Update()
{
	int cnt = 0;
	if (openFlag_)
	{
		for (auto&& list : list_)
		{

			if (list->IsHit(lpMouseController.GetPos() + pos_))
			{
				list->PushFunction();
				break;
			}
		}
	}
	else
	{
		if (list_.front()->IsHit(lpMouseController.GetPos() + pos_))
		{
			list_.front()->PushFunction();
		}
	}
}

void PullDown::Draw()
{
	int defScreen = GetDrawScreen();
	SetDrawScreen(screen_);
	ClearDrawScreen();

	for (auto&& list : list_)
	{
		list->Draw();
	}

	SetDrawScreen(defScreen);
	DrawRectGraph(pos_.x, pos_.y, 0, 0, size_.x, size_.y, screen_, true);
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + 20, 0x000000, false);
	if (openFlag_)
	{
		//DrawRectGraph(pos_.x, pos_.y,0,0, size_.x, size_.y, screen_, true);
	}
	else
	{

	}
}
