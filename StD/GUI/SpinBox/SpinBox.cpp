#include "SpinBox.h"
#include<DxLib.h>

SpinBox::SpinBox(VECTOR2 pos,int xSize,BoxType type, VECTOR2 cOffset, int fontHandle)
{
	pos_ = pos;
	type_ = type;
	fontHandle_ = fontHandle;
	size_ = VECTOR2(xSize, (fontHandle != -1 ? GetFontSizeToHandle(fontHandle) : GetFontSize()));
	button_.first = std::make_unique<ImageRectButton>(pos + cOffset + size_ - VECTOR2(24 + 2, size_.y - 2), VECTOR2(24, 12), L"./data/image/allow_up.png", L"./data/image/allow_up_push.png", [&]() {selKey_ -= (selKey_ - 1 < 0 ? 0 : 1);  return true; });
	button_.second = std::make_unique<ImageRectButton>(pos + cOffset + size_ - VECTOR2(24 + 2, 12 + 2), VECTOR2(24, 12), L"./data/image/allow_down.png", L"./data/image/allow_down_push.png", [&]() {selKey_ += (selKey_ + 1 >= nowSize_ ? 0 : 1);  return true; });
	Init();
}

SpinBox::SpinBox(VECTOR2 pos, VECTOR2 size, BoxType type, VECTOR2 cOffset)
{
	pos_ = pos;
	type_ = type;
	size_ = size;
	fontHandle_ = CreateFontToHandle(NULL, size_.y, 1);
	button_.first = std::make_unique<ImageRectButton>(pos + cOffset + size_ - VECTOR2(24 + 2, size_.y - 2), VECTOR2(24, 12), L"./data/image/allow_up.png", L"./data/image/allow_up_push.png", [&]() {selKey_ -= (selKey_ - 1 < 0 ? 0 : 1);  return true; });
	button_.second = std::make_unique<ImageRectButton>(pos + cOffset + size_ - VECTOR2(24 + 2, 12 + 2), VECTOR2(24, 12), L"./data/image/allow_down.png", L"./data/image/allow_down_push.png", [&]() {selKey_ += (selKey_ + 1 >= nowSize_ ? 0 : 1);  return true; });
	Init();
}

void SpinBox::Init()
{
	selKey_ = 0;
	nowSize_ = 0;

	button_.first->SetAuto();
	button_.first->SetReversePush();
	button_.first->SetSound();
	button_.second->SetAuto();
	button_.second->SetReversePush();
	button_.second->SetSound();
}


SpinBox::~SpinBox()
{
}

bool SpinBox::Update()
{
	bool flag = 0;
	flag |= button_.first->Update();
	flag |= button_.second->Update();

	return flag;
}

