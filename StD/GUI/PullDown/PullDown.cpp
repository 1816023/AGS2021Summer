#include "PullDown.h"
#include "../../MouseController.h"
#include <DxLib.h>
PullDown::PullDown(VECTOR2 pos, int xSize,int fontHandle)
{
	fontHandle_ = fontHandle!=0?fontHandle: GetDefaultFontHandle();
	const int fontSize = GetFontSizeToHandle(fontHandle_);
	pos_=pos;
	screen_ = MakeScreen(xSize, 2560);
	GetGraphSize(screen_, &size_.x, &size_.y);
	selKey_ = 0;
	list_.emplace_back(std::make_unique<RectButton>( pos_+VECTOR2(size_.x-fontSize, 0), pos_+VECTOR2(size_.x,fontSize), 0xfffffff, [&]() {return openFlag_ = ~openFlag_; }, VECTOR2()));
	list_.back()->SetFont(fontHandle_);
	list_.back()->SetString("Бе", VECTOR2(2,2));
	list_.back()->SetTag(1);
	list_.back()->SetSound();
	openFlag_ = 0;
}

PullDown::~PullDown()
{
}

bool PullDown::Add(std::string str)
{
	auto listSize = list_.size()-1;
	const int fontSize = GetFontSizeToHandle(fontHandle_);
	list_.emplace_back(std::make_unique<RectButton>(VECTOR2(0, listSize * fontSize), VECTOR2(size_.x , fontSize + listSize * fontSize), 0xffffff, [&, listSize]() {selKey_ = listSize; openFlag_ = false; return true; }, VECTOR2()));
	list_.back()->SetString(str, VECTOR2(2,2));
	list_.back()->SetSound();
	list_.back()->SetFont(fontHandle_);
	return true;
}

void PullDown::Update()
{
	int cnt = 0;
	for (auto&& list : list_)
	{
		list->Update();
	}
	scroll_ += openFlag_?lpMouseController.GetWheel()*3:0;
	scroll_ = scroll_ > 0 ? 0 : scroll_;
	if (lpMouseController.GetClickTrg(MOUSE_INPUT_LEFT))
	{
		if (openFlag_)
		{
			

			for (auto&& list : list_)
			{
				if (list->GetTag() == 1)
				{
					if (list_.back()->IsHit(lpMouseController.GetPos()))
					{
						list_.back()->PushFunction();
					}

				}
				else
				{
					if (list->IsHit(lpMouseController.GetPos() - pos_-VECTOR2(0, scroll_)))
					{
						list->PushFunction();
						//list_.back()->SetPos(VECTOR2(size_.x - 20,20*selKey_),VECTOR2(size_.x,20+20*selKey_));
						break;
					}
				}
			}
		}
		else
		{
			if (list_.front()->IsHit(lpMouseController.GetPos()))
			{
				list_.front()->PushFunction();
			}
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
		if (list->GetTag() != 1)
		{
			list->Draw();

		}
	}

	SetDrawScreen(defScreen);
	const int fontSize = GetFontSizeToHandle(fontHandle_);
	DrawRectGraph(pos_.x, pos_.y, 0, fontSize*selKey_, size_.x, fontSize, screen_, true);
	list_.front()->Draw();
	if (openFlag_)
	{
		//DrawRectGraph(pos_.x, pos_.y,0,0, size_.x, size_.y, screen_, true);
		DrawRectGraph(pos_.x, pos_.y,0,0-scroll_,size_.x,size_.y-scroll_, screen_, true);
		DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0xffffff, false);

	}
	else
	{
		DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + fontSize, 0xffffff, false);
		
	}
}

std::string PullDown::GetSelStr()
{
	return list_[selKey_+1]->GetStr();
}
