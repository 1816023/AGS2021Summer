#include "SpinBoxForBool.h"
#include <DxLib.h>
SpinBoxForBool::SpinBoxForBool(VECTOR2 pos, int xSize, VECTOR2 cOffset, int fontHandle):SpinBox(pos,xSize,BoxType::BOOL, cOffset, fontHandle)
{
	array_[0] = true;
	array_[1] = false;
}

SpinBoxForBool::~SpinBoxForBool()
{
}

void SpinBoxForBool::Draw()
{
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0x000000, true);
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0xffffff, false);
	if (fontHandle_ != -1)
	{
		DrawStringToHandle(pos_.x, pos_.y, array_[selKey_]?L"TRUE":L"FALSE", 0xffffff, fontHandle_);
	}
	else
	{
		DrawString(pos_.x, pos_.y, array_[selKey_] ? L"TRUE" : L"FALSE", 0xffffff);

	}
	button_.first->Draw();
	button_.second->Draw();
}

const int SpinBoxForBool::GetSelData() const
{
	return array_[selKey_];
}
