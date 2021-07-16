#include "SpinBoxForFloat.h"
#include <DxLib.h>
SpinBoxForFloat::SpinBoxForFloat(VECTOR2 pos, int xSize, int NumOfDigits, int NumOfDigitsOfDecmal, int fontHandle) :SpinBox(pos, xSize, BoxType::FLOAT, fontHandle)
{
	NumOfDigits_ = NumOfDigits;
	NumOfDigitsOfDecmal_ = NumOfDigitsOfDecmal;
}

SpinBoxForFloat::~SpinBoxForFloat()
{
}

void SpinBoxForFloat::Draw()
{
	std::wstring str = L"%" + std::to_wstring(NumOfDigits_) + L"." + std::to_wstring(NumOfDigitsOfDecmal_) + L"f";
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0x000000, true);
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0xffffff, false);
	if (vec_.size() != 0)
	{
		if (fontHandle_ == -1)
		{
			DrawFormatString(pos_.x, pos_.y, 0xffffff, str.c_str(), vec_[selKey_]);
		}
		else
		{
			DrawFormatStringToHandle(pos_.x, pos_.y, 0xffffff, fontHandle_, str.c_str(), vec_[selKey_]);
		}
	}
	button_.first->Draw();
	button_.second->Draw();
}

const float SpinBoxForFloat::GetSelData() const
{
	return vec_[selKey_];
}

void SpinBoxForFloat::AddData(float data)
{
	nowSize_ = vec_.size();
	vec_.push_back(data);
}

void SpinBoxForFloat::DeleteData()
{
	vec_.pop_back();
	nowSize_ = vec_.size();
}

bool SpinBoxForFloat::DeleteData(float data)
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
