#pragma once
#include "../Scene/CustomMapScene.h"
#include "CustomState.h"
#include "../StringUtil.h"
#include "../Map/Astar.h"
#define CUSTOM dynamic_cast<Custom*>(scene->cusMap_.get())

struct MapCustom:public CustomStateBase
{
	MapCustom() {};
	~MapCustom() {};
	bool Init(CustomMapScene* scene)override
	{
		/*astar_ = std::make_unique<Astar>(*scene->cusMap_);*/
		const int bSize = 64;
		const int bSpace = 20;
		const int basePosX = SELECT_UI_POS.first.x + bSpace;
		const int basePosY = SELECT_UI_POS.first.x + bSize + bSpace;
		// �{�^���̍쐬
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, bSpace * 2), VECTOR2(basePosY, bSize + bSpace * 2), VECTOR2(10, 10), 0x007fff, [&]() {selChip_ = MapChipName::MAINSTAY; return true; }, VECTOR2()));
		buttonText_.emplace_back(ButtonText{ "�����_",0xffffff,VECTOR2(basePosX,  bSpace * 2 - GetFontSize()) });
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace), bSpace * 2), VECTOR2(basePosY + (bSize + bSpace), bSize + bSpace * 2), VECTOR2(10, 10), 0xff0f0f, [&]() {selChip_ = MapChipName::SPAWNER; return true; }, VECTOR2()));
		buttonText_.emplace_back(ButtonText{ "�G�o��", 0xffffff, VECTOR2(basePosX + (bSize + bSpace), bSpace * 2 - GetFontSize()) });
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace) * 2, bSpace * 2), VECTOR2(basePosY + (bSize + bSpace) * 2, bSize + bSpace * 2), VECTOR2(10, 10), 0xfff00, [&]() {selChip_ = MapChipName::ROOT; return true; }, VECTOR2()));
		buttonText_.emplace_back(ButtonText{ "�G�N�U",0xffffff,VECTOR2(basePosX + (bSize + bSpace) * 2, bSpace * 2 - GetFontSize()) });
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, bSpace + (bSize + bSpace * 2)), VECTOR2(basePosY, bSize + bSpace + (bSize + bSpace * 2)), VECTOR2(10, 10), 0xe3e3e3, [&]() {selChip_ = MapChipName::FIELD; return true; }, VECTOR2()));
		buttonText_.emplace_back(ButtonText{ "���@�z�u",0xffffff,VECTOR2(basePosX, bSpace + (bSize + bSpace * 2) - GetFontSize()) });
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace), bSpace + (bSize + bSpace * 2)), VECTOR2(basePosY + (bSize + bSpace), bSize + bSpace + (bSize + bSpace * 2)), VECTOR2(10, 10), 0x333333, [&]() {selChip_ = MapChipName::WALL; return true; }, VECTOR2()));
		buttonText_.emplace_back(ButtonText{ "�ݒu�s��",0xffffff,VECTOR2(basePosX + (bSize + bSpace), bSpace + (bSize + bSpace * 2) - GetFontSize()) });
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace) * 2, bSpace + (bSize + bSpace * 2)), VECTOR2(basePosY + (bSize + bSpace) * 2, bSize + bSpace + (bSize + bSpace * 2)), VECTOR2(10, 10), 0xffffff, [&]() {selChip_ = MapChipName::MAX; return true; }, VECTOR2()));
		buttonText_.emplace_back(ButtonText{ "�I������",0xffffff,VECTOR2(basePosX + (bSize + bSpace) * 2, bSpace + (bSize + bSpace * 2) - GetFontSize()) });
		// �V�X�e���n�̃{�^��
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, SELECT_UI_POS.second.y - bSize / 2 - bSpace), VECTOR2(basePosX + bSize, SELECT_UI_POS.second.y - bSpace), VECTOR2(10, 10), 0xffffff, [&,scene]() {
			scene->nowState_ = CustomState::SELECT_FILE;
			scene->custom_[scene->nowState_]->Init(scene);
			Delete();
			return false; }, VECTOR2()));
		button_.back()->SetString("Back", VECTOR2(bSize / 2 - GetDrawStringWidth(L"Back", GetStringLength(L"Back")) / 2, bSize / 4 - GetFontSize() / 2));
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX+bSize+bSpace, SELECT_UI_POS.second.y - bSize / 2 - bSpace), VECTOR2(basePosX + bSize*2+bSpace, SELECT_UI_POS.second.y - bSpace), VECTOR2(10, 10), 0xffffff, [&,scene]() {
			scene->nowState_ = CustomState::ENEMY_CUSTOM;
			scene->custom_[scene->nowState_]->Init(scene);
			Delete();
			return true; }, VECTOR2()));
		button_.back()->SetString("Next", VECTOR2(bSize / 2 - GetDrawStringWidth(L"Next", GetStringLength(L"Next")) / 2, bSize / 4 - GetFontSize() / 2));
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(SELECT_UI_POS.second.x - bSize - bSpace, SELECT_UI_POS.second.y - bSize / 2 - bSpace), VECTOR2(SELECT_UI_POS.second.x - bSpace, SELECT_UI_POS.second.y - bSpace), VECTOR2(10, 10), 0xffffff, [&,scene]() {
			if (errorNum_=scene->SaveCheck()==0)
			{
				CUSTOM->SaveFile(); 
				return  true; 
			}
			else
			{
				return false;
			}
			}, VECTOR2()));
		button_.back()->SetString("Save", VECTOR2(bSize / 2 - GetDrawStringWidth(L"Save", GetStringLength(L"Save")) / 2, bSize / 4 - GetFontSize() / 2));
		//button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, bSize * 2 + bSpace * 4), VECTOR2(basePosY, bSize * 3 + bSpace * 4), VECTOR2(10, 10), 0xffffff,
		//	[&,scene]()
		//	{
		//		const auto& spawners = scene->cusMap_->Getspawner();
		//		const auto& mainStay = scene->cusMap_->GetMainStay();
		//		if (mainStay != VECTOR2(-1, -1) && spawners.size() != 0)
		//		{
		//			astar_->AstarStart(mainStay, spawners.at(0));
		//		}
		//		return false;
		//	}, VECTOR2()));
		//buttonText_.emplace_back(ButtonText{ "���[�g�쐬",0xffffff,VECTOR2(basePosX, bSize * 2 + bSpace * 4 - GetFontSize()) });
		
		// �S�Ẵ{�^��������������
		for (auto&& b : button_)
		{
			b->SetAuto();
		}
		scene->blendAlpha_ = 256;
		selChip_ = MapChipName::MAX;
		scene->LoadText();
		errorNum_ = 0;
		// �G���[�̓��e
		// �ő�񐔁i���{��S�p��16�����j
		// �ő�s���i6�s�j
		errorText_.push_back("");
		errorText_.push_back("���_�ƃX�|�i�[�̐����������܂��B\n�ő吔�͊e2�܂łł��B");
		errorText_.push_back("���_�̐����������܂��B\n�ő吔��2�܂łł��B");
		errorText_.push_back("�X�|�i�[�̐����������܂��B\n�ő吔��2�܂łł��B");
		return false;

	}
	void Update(CustomMapScene* scene)override
	{
		for (auto&& list : button_)
		{
			if (list->Update())
			{
				break;
			}
		}
		VECTOR2 mPos = lpMouseController.GetOffsetPos();
		auto cPos = lpApplication.GetCamera().GetPos()* 3.0f;
		if (lpMouseController.GetClicking(MOUSE_INPUT_LEFT))
		{
			if (mPos.x > SELECT_UI_POS.first.x)
			{
			}
			else
			{
				scene->cusMap_->SetChip(VecICast(cPos + mPos), selChip_);
			}
		}

		scene->blendAlpha_ += 2;

	}

	void Draw(CustomMapScene* scene)override
	{
		// �g�\��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawRoundRect(SELECT_UI_POS.first.x, SELECT_UI_POS.first.y, SELECT_UI_POS.second.x, SELECT_UI_POS.second.y, 20, 20, 0x555555, true);
		DrawRoundRect(SELECT_UI_POS.first.x, SELECT_UI_POS.first.y, SELECT_UI_POS.second.x, SELECT_UI_POS.second.y, 20, 20, 0xffffff, false);
		DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0x555555, true);
		DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0xffffff, false);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
		// �������̕\��
		DrawString(TEXT_UI_POS.first.x + 3, TEXT_UI_POS.first.y + (TEXT_UI_POS.second.y - TEXT_UI_POS.first.y) / 5, _StW(scene->textData_[selChip_]).c_str(), 0xffffff);
		VECTOR2 mPos = lpMouseController.GetPos();
		for (auto&& list : button_)
		{
			list->Draw();
		}
		for (auto list : buttonText_)
		{
			DrawString(list.pos_.x, list.pos_.y, _StW(list.str_).c_str(), list.color_);
		}
		DrawString(SELECT_UI_POS.first.x + 10, SELECT_UI_POS.first.y + (SELECT_UI_POS.second.y - SELECT_UI_POS.first.y) / 1.5f, _StW(errorText_[errorNum_]).c_str(), 0xff0000);
#ifdef _DEBUG

		DrawFormatString(mPos.x, mPos.y + 10, 0x00ff00, L"%d:%d", lpMouseController.GetOffsetPos().x,lpMouseController.GetOffsetPos().y );
		DrawFormatString(mPos.x, mPos.y + 30, 0x0000ff, L"%d:%d", mPos.x + static_cast<int>(lpApplication.GetCamera().GetPos().x), mPos.y + static_cast<int>(lpApplication.GetCamera().GetPos().y));
#endif // _DEBUG

	}
	void Delete() {
		button_.clear();
		buttonText_.clear();
	}
private:
	MapChipName selChip_;
	std::list<std::unique_ptr<Button>>button_;
	std::list<ButtonText>buttonText_;
	//// Astar�N���X�̃|�C���^�[
	//std::unique_ptr<Astar>astar_;
	int errorNum_;
	std::vector<std::string> errorText_;
};