#pragma once
#include "CustomState.h"
#include "../Scene/CustomMapScene.h"
struct SetState:public CustomStateBase
{
	SetState() {};
	~SetState() {};
	bool Init(CustomMapScene*scene)override
	{
		buttomList_.emplace_back(std::make_unique<RectButton>(VECTOR2(), VECTOR2(), 0xffffff, []() {return true; }, VECTOR2()));
		return false;
	}
	void Update(CustomMapScene *scene)override
	{
	}
	void Draw(CustomMapScene* scene)override
	{
	
	}
private:
	void NewCreate()
	{

		//DrawString(0, 0, L"Set", 0xffffff);
	//DrawString(0, STRING_HIGHT, L"�}�b�v�̉����F", 0xffffff);
	//DrawString(0, STRING_HIGHT + LINE_SPACING, L"�}�b�v�̍����F", 0xffffff);
	//DrawString(0, STRING_HIGHT + LINE_SPACING * 2, L"�t�@�C�����F", 0xffffff);
	//DrawString(0, STRING_HIGHT * 2 + LINE_SPACING * 2, L"�����̕����ƃX�y�[�X�͎g�p�ł��܂���\n�u���@�^�@�F�@���@�H�@�h�@���@���@�b�@.�@& ( ) [ ] { } ^ = ; ! ' + , ` ~�v", 0xff9999);
	//int tmpFlag = 0;
	//// ��������
	//scene->mapSizeX_ = KeyInputNumber(GetDrawStringWidth(L"�}�b�v�̉����F", GetStringLength(L"�}�b�v�̉����F")) + 1, STRING_HIGHT, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	//if (scene->mapSizeX_<MIN_MAP_SIZE || scene->mapSizeX_>MAX_MAP_SIZE)
	//{
	//	return;
	//}
	//else
	//{
	//	tmpFlag++;
	//}
	//DrawFormatString(GetDrawStringWidth(L"�}�b�v�̉����F", GetStringLength(L"�}�b�v�̉����F")) + 1, STRING_HIGHT, 0xffffff, L"%d", scene->mapSizeX_);
	//// �c������
	//scene->mapSizeY_ = KeyInputNumber(GetDrawStringWidth(L"�}�b�v�̍����F", GetStringLength(L"�}�b�v�̍����F")) + 1, STRING_HIGHT + LINE_SPACING, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	//if (scene->mapSizeY_<MIN_MAP_SIZE || scene->mapSizeY_>MAX_MAP_SIZE)
	//{
	//	return;
	//}
	//else
	//{
	//	tmpFlag++;
	//}
	//DrawFormatString(GetDrawStringWidth(L"�}�b�v�̍����F", GetStringLength(L"�}�b�v�̍����F")) + 1, STRING_HIGHT + LINE_SPACING, 0xffffff, L"%d", scene->mapSizeY_);
	//// ���O����
	//if (KeyInputString(GetDrawStringWidth(L"�t�@�C�����F", GetStringLength(L"�t�@�C�����F")) + 1, STRING_HIGHT + LINE_SPACING * 2, MAX_NAME_SIZE, scene->fileName_, true) != 1)
	//{
	//	return;
	//}
	//else {
	//	// �t�@�C�����ɔ�Ή��������܂܂�Ă��邩
	//	if (scene->FileNameErrorCheck(scene->fileName_))
	//	{
	//		return;
	//	}
	//	tmpFlag++;
	//}
	//if (tmpFlag >= 3)
	//{
	//	scene->nowState_ = CustomState::MAP_CUSTOM;
	//	scene->map_->SetUp(scene->fileName_, VECTOR2(scene->mapSizeX_, scene->mapSizeY_));
	//	scene->custom_[scene->nowState_]->Init(scene);
	//	
	//	
	//}
	}
	// �t�@�C�����̃��X�g�i�[�p
	std::list<std::string>fileList_;
	std::list<std::unique_ptr<Button>>buttomList_;
	bool isNewCreate_;
};