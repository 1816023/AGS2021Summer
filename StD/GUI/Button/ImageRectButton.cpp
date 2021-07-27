#include <DxLib.h>
#include "../../Mng/ImageMng.h"
#include "ImageRectButton.h"
#include "../../StringUtil.h"

ImageRectButton::ImageRectButton(VECTOR2 pos, VECTOR2 size, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()> func)
{
	pos_ = pos;
	size_ = size;
	imagePath_ = imagePath;
	pushImagePath_ = pushImagePath;
	func_ = func;
	type_ = ButtonType::BoxImage;
}

ImageRectButton::ImageRectButton(VECTOR2 size, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()> func)
{
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
	const int push = size_.y / 5;
	if (isPush_)
	{
		DrawGraph(pos_.x + offset_.x, pos_.y + offset_.y, IMAGE_ID(pushImagePath_.c_str()), true);
		//DrawRotaGraph(pos_.x + (size_.x*scale_) / 2, pos_.y + (size_.y*scale_)/2, scale_, 0, IMAGE_ID(pushImagePath_.c_str()), true);
		if (fontHandle_ != -1)
		{
			DrawStringToHandle(pos_.x + sPos_.x, pos_.y + sPos_.y + push, _StW(str_).c_str(), ~color_, fontHandle_);
		}
		else
		{
			DrawString(pos_.x + sPos_.x, pos_.y + sPos_.y + push, _StW(str_).c_str(), ~color_);
		}
	}
	else
	{
		DrawGraph(pos_.x + offset_.x, pos_.y + offset_.y, IMAGE_ID(imagePath_.c_str()), true);
		//DrawRotaGraph(pos_.x + (size_.x*scale_) / 2, pos_.y + (size_.y*scale_)/2, scale_, 0, IMAGE_ID(imagePath_.c_str()), true);

		if (fontHandle_ != -1)
		{
			DrawStringToHandle(pos_.x + sPos_.x, pos_.y + sPos_.y , _StW(str_).c_str(), ~color_, fontHandle_);
		}
		else 
		{
			DrawString(pos_.x + sPos_.x, pos_.y + sPos_.y, _StW(str_).c_str(), ~color_);
		}
	}
}

