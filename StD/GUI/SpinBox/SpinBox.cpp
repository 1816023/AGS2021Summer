#include "SpinBox.h"
#include<DxLib.h>

SpinBox::SpinBox(VECTOR2 pos,int xSize,BoxType type, int fontHandle)
{
	pos_ = pos;
	type_ = type;
	fontHandle_ = fontHandle;
	size_ = VECTOR2(xSize, (fontHandle != -1 ? GetFontSizeToHandle(fontHandle) : GetFontSize()));
	selKey_ = 0;
	nowSize_ = 0;
	button_.first = std::make_unique<ImageRectButton>(pos+size_ - VECTOR2(24,24),VECTOR2(24,12), L"./data/image/allow_up.png", L"./data/image/allow_up_push.png", [&]() {selKey_ -= (selKey_ - 1 < 0 ? 0 : 1);  return true; }, VECTOR2());
	button_.second = std::make_unique<ImageRectButton>(pos+size_ - VECTOR2(24,12), VECTOR2(24, 12), L"./data/image/allow_down.png", L"./data/image/allow_down_push.png", [&]() {selKey_ += (selKey_ + 1>= nowSize_ ? 0 : 1);  return true; }, VECTOR2());
	button_.first->SetAuto();
	button_.first->SetReversePush();
	button_.first->SetSound();
	button_.second->SetAuto();
	button_.second->SetReversePush();
	button_.second->SetSound();
	buttonScreen_ = MakeScreen(24, 24, 0);
}

SpinBox::~SpinBox()
{
	DeleteFontToHandle(fontHandle_);
}

bool SpinBox::Update()
{
	bool flag = 0;
	flag |= button_.first->Update();
	flag |= button_.second->Update();

	return flag;
}

int SpinBox::ButtonDraw()
{
	int defScreen = GetDrawScreen();
	SetDrawScreen(buttonScreen_);
	ClearDrawScreen();

	button_.first->Draw();
	button_.second->Draw();

	SetDrawScreen(defScreen);
	return buttonScreen_;
}

