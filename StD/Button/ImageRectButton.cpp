#include <DxLib.h>
#include "../Mng/ImageMng.h"
#include "ImageRectButton.h"

ImageRectButton::ImageRectButton(VECTOR2 pos, VECTOR2 size, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()> func, VECTOR2 offset)
	:Button(offset)
{
	pos_ = pos;
	size_ = size;
	imagePath_ = imagePath;
	pushImagePath_ = pushImagePath;
	func_ = func;
	type_ = ButtonType::BoxImage;

}

ImageRectButton::~ImageRectButton()
{
}


bool ImageRectButton::IsHit(VECTOR2 mPos)
{
	if (!((mPos.x < pos_.x || mPos.y < pos_.y) || (mPos.x<pos_.x || mPos.y>pos_.y + size_.y) || (mPos.x > pos_.x + size_.x || mPos.y < pos_.y) || (mPos.x > pos_.x + size_.x || mPos.y > pos_.y + size_.y)))
	{
		isPush_ = true;
		return true;
	}
	else
	{
		isPush_ = false;
		return false;
	}
}


void ImageRectButton::Draw()
{
	if (isPush_)
	{
		DrawGraph(pos_.x + offset_.x, pos_.x + offset_.y, IMAGE_ID(pushImagePath_.c_str()), true);
	}
	else
	{
		DrawGraph(pos_.x + offset_.x, pos_.x + offset_.y, IMAGE_ID(imagePath_.c_str()), true);
	}

}
