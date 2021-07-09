#include "SpinBoxForInt.h"
#include <DxLib.h>
SpinBoxForInt::SpinBoxForInt(VECTOR2 pos, int xSize, int fontHandle) :SpinBox(pos,xSize, BoxType::INT, fontHandle)
{

}

SpinBoxForInt::~SpinBoxForInt()
{
}

bool SpinBoxForInt::Update()
{
	return false;
}

void SpinBoxForInt::Draw()
{
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0x000000, true);
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0xffffff, false);
	if (fontHandle_ == -1)
	{
		DrawFormatString(pos_.x, pos_.y, 0xffffff, L"%d", vec_[selKey_]);
	}
	else
	{
		DrawFormatStringToHandle(pos_.x, pos_.y, 0xffffff,fontHandle_, L"%d", vec_[selKey_]);
	}
}

const int SpinBoxForInt::GetSelData() const
{
	return vec_[selKey_];
}

void SpinBoxForInt::AddData(int data)
{
	vec_.push_back(data);
	nowSize_ = vec_.size();
}

bool SpinBoxForInt::DeleteData()
{
	auto itr = vec_.erase(--vec_.end());
	nowSize_ = vec_.size();
	return itr!=vec_.end();
}

bool SpinBoxForInt::DeleteData(int data)
{
	auto itr = std::find(vec_.begin(), vec_.end(), data);
	if (itr == vec_.end())
	{
		return false;
	}
	itr = vec_.erase(itr);
	nowSize_ = vec_.size();
	return itr!=vec_.end();
}
