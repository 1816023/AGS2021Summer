#include "SpinBoxForString.h"
#include <DxLib.h>
#include "../../StringUtil.h"
SpinBoxForString::SpinBoxForString(VECTOR2 pos, int xSize, VECTOR2 cOffset, int fontHandle) :SpinBox(pos, xSize, BoxType::STRING, cOffset, fontHandle)
{
}
SpinBoxForString::~SpinBoxForString()
{
}

bool SpinBoxForString::Update()
{
	button_.first->Update();
	button_.second->Update();

	return false;
}

void SpinBoxForString::Draw()
{
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0x000000, true);
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0xffffff, false);
	if (vec_.size() != 0)
	{
		if (fontHandle_ == -1)
		{
			DrawString(pos_.x, pos_.y, _StW(vec_[selKey_]).c_str(), 0xffffff);
		}
		else
		{
			DrawStringToHandle(pos_.x, pos_.y, _StW(vec_[selKey_]).c_str(), 0xffffff,fontHandle_);
		}
	}
	button_.first->Draw();
	button_.second->Draw();
}

const std::string SpinBoxForString::GetSelData() const
{
	return vec_[selKey_];
}

void SpinBoxForString::AddData(std::string data)
{
	vec_.push_back(data);
	nowSize_ = vec_.size();

}

void SpinBoxForString::DeleteData()
{
	vec_.pop_back();
}

bool SpinBoxForString::DeleteData(std::string data)
{
	auto itr = std::find(vec_.begin(), vec_.end(), data);
	if (itr == vec_.end())
	{
		return false;
	}
	itr = vec_.erase(itr);
	nowSize_ = vec_.size();
	return itr != vec_.end();
}
