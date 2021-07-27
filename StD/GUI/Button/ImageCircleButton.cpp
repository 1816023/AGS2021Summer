#include <DxLib.h>
#include "../../Mng/ImageMng.h"
#include "ImageCircleButton.h"

ImageCircleButton::ImageCircleButton(VECTOR2 pos, int radius, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()> func)
{
	pos_ = pos;
	radius_ = radius;
	imagePath_ = imagePath;
	pushImagePath_ = pushImagePath;
	func_ = func;
	type_ = ButtonType::CircleImage;
}

ImageCircleButton::ImageCircleButton(int radius, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()> func)
{
	radius_ = radius;
	imagePath_ = imagePath;
	pushImagePath_ = pushImagePath;
	func_ = func;
	type_ = ButtonType::CircleImage;
}

ImageCircleButton::~ImageCircleButton()
{
}


bool ImageCircleButton::IsHit(VECTOR2 mPos)
{
	auto tmp = pos_ - mPos;
	auto r = std::sqrt((tmp.x * tmp.x) + (tmp.y * tmp.y));
	if (r <= radius_)
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

void ImageCircleButton::Draw()
{
	
	if (isPush_)
	{
		DrawGraph(pos_.x, pos_.x, IMAGE_ID(pushImagePath_.c_str()), true);
	}
	else
	{
		DrawGraph(pos_.x, pos_.x, IMAGE_ID(imagePath_.c_str()), true);
	}

}
