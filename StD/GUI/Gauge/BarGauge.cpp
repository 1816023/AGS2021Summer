#include "BarGauge.h"
#include <DxLib.h>
BarGauge::BarGauge(VECTOR2 pos, VECTOR2 size, int maxGauge)
{
	pos_ = pos;
	size_ = size;
	gauge_ = 0;
	isView_ = false;
	isBackColor = false;
	gaugeColor_ = 0x000000;
	frameColor_ = 0xffffff;
	backColor_ = 0xffffff;
	maxGauge_ = maxGauge;
}

BarGauge::~BarGauge()
{
}

bool BarGauge::Update()
{
	return false;
}

void BarGauge::Draw()
{
	if (isBackColor)
	{
		DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, backColor_, true);
	}
	float par = static_cast<float>(gauge_) / static_cast<float>(maxGauge_);
	DrawBox(pos_.x, pos_.y, pos_.x + (size_.x * par), pos_.y + size_.y, gaugeColor_, true);
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, frameColor_, false);
}

int BarGauge::Add(int num)
{
	return gauge_ += num;
}

int BarGauge::Sub(int num)
{
	return gauge_ -= num;
}

void BarGauge::SetViewNumber(VECTOR2 pos)
{
	strPos_ = pos;
	return;
}

void BarGauge::SetColor(int gaugeColor, int frameColor)
{
	gaugeColor_ = gaugeColor;
	frameColor_ = frameColor;
}

void BarGauge::SetBackColor(bool isView, int color)
{
	isBackColor = isView;
	backColor_ = color;
}

void BarGauge::ChangeMaxGauge(int num)
{
	maxGauge_ = num;
}
