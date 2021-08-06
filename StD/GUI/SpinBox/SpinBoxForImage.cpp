#include "SpinBoxForImage.h"
#include "../../Mng/ImageMng.h"
#include "../../StringUtil.h"
#include <DxLib.h>
SpinBoxForImage::SpinBoxForImage(VECTOR2 pos, VECTOR2 size, VECTOR2 cOffset):SpinBox(pos,size,BoxType::IMAGE, cOffset)
{

}

SpinBoxForImage::~SpinBoxForImage()
{
}

void SpinBoxForImage::Draw()
{
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0x000000, true);

	if (vec_.size() != 0)
	{
		DrawGraph(pos_.x, pos_.y, vec_[selKey_], true);
	}
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0xffffff, false);

	button_.first->Draw();
	button_.second->Draw();
}

const int SpinBoxForImage::GetSelData() const
{
	return vec_[selKey_];
}

void SpinBoxForImage::AddData(std::string path)
{
	vec_.push_back(IMAGE_ID(_StW(path)));
}

void SpinBoxForImage::AddData(int handle)
{
	vec_.push_back(handle);
	nowSize_ = vec_.size();
}

void SpinBoxForImage::DeleteData()
{
	vec_.pop_back();
	nowSize_ = vec_.size();
}

bool SpinBoxForImage::DeleteData(std::string data)
{
	return DeleteData(IMAGE_ID(_StW(data)));
}

bool SpinBoxForImage::DeleteData(int data)
{
	auto itr = std::find(vec_.begin(), vec_.end(),data);
	if (itr == vec_.end())
	{
		return false;
	}
	itr = vec_.erase(itr);
	nowSize_ = vec_.size();
	return itr != vec_.end();
}

void SpinBoxForImage::StartEnd(bool key)
{
	selKey_ = key ? 0 : vec_.size()-1;
}
