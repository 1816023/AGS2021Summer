#include "Box.h"
#include <DxLib.h>

Box::Box(VECTOR2 pos, VECTOR2 size, int color, bool fillF)
{
	pos_ = pos;
	size_ = size;
	outColor_ = color;
	inColor_ = -1;
	fillF_ = fillF;
}

Box::Box(VECTOR2 pos, VECTOR2 size, int outColor, int inColor)
{
	pos_ = pos;
	size_ = size;
	outColor_ = outColor;
	inColor_ = inColor;
	fillF_ = false;
}

bool Box::Update()
{
	return false;
}

void Box::Draw()
{
	if (inColor_ != -1)
	{
		DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, inColor_, true);
	}
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, outColor_, fillF_);
}
