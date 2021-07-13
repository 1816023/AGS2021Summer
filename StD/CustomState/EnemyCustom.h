#pragma once
#include "CustomState.h"
#include "../Scene/CustomMapScene.h"
#include "../GUI/ScrollList/ImageList.h"
#include "../GUI/ScrollList/StringList.h"
#include "../GUI/Button/ImageRectButton.h"
#include "../Mng/ImageMng.h"
#include "../Mng/ImageMng.h"
#include "../GUI/SpinBox/SpinBoxForString.h"
#include "../GUI/SpinBox/SpinBoxForInt.h"
#include "../GUI/SpinBox/SpinBoxForImage.h"
#define CUSTOM dynamic_cast<Custom*>(scene->map_.get())

struct EnemyCustom :public CustomStateBase
{
	EnemyCustom(){};
	~EnemyCustom() {};
	~EnemyCustom() { };
	bool Init(CustomMapScene* scene)
	{
		const int bSize = 64;
		const int bSpace = 10;
		const int basePosX = SELECT_UI_POS.first.x + bSpace;
		const int basePosY = SELECT_UI_POS.first.x + bSize + bSpace;
		enemyH_.try_emplace(EnemyType::Circle, IMAGE_ID(L"./data/image/circle.png"));

		astar_ = std::make_unique<Astar>(*scene->cusMap_);
		const auto& spawners = scene->cusMap_->GetSpawner();
		const auto& mainStay = scene->cusMap_->GetMainStay();
		fontHandle_ = CreateFontToHandle(NULL, 30, 1);
		auto strSize=VECTOR2(GetDrawStringWidthToHandle(L"�X�|�i�[ ",GetStringLength(L"�X�|�i�[ "), fontHandle_),GetFontSizeToHandle(fontHandle_));
		spinBoxS_.try_emplace("�X�|�i�[", std::make_unique<SpinBoxForInt>(VECTOR2(basePosX,0 )+strSize, 100, fontHandle_));
		spinBoxS_.try_emplace("Wave", std::make_unique<SpinBoxForInt>(VECTOR2(basePosX, strSize.y+bSpace) + strSize, 100, fontHandle_));
		dynamic_cast<SpinBoxForInt*>(spinBoxS_["Wave"].get())->AddData(3);
		dynamic_cast<SpinBoxForInt*>(spinBoxS_["Wave"].get())->AddData(2);
		dynamic_cast<SpinBoxForInt*>(spinBoxS_["Wave"].get())->AddData(1);
		spinBoxS_.try_emplace("���[�g", std::make_unique<SpinBoxForInt>(VECTOR2(basePosX, (strSize.y + bSpace)*2) + strSize, 100, fontHandle_));
		dynamic_cast<SpinBoxForInt*>(spinBoxS_["���[�g"].get())->AddData(1);
		spinBoxS_.try_emplace("�G���", std::make_unique<SpinBoxForImage>(VECTOR2(basePosX, (strSize.y + bSpace) * 3) + strSize, VECTOR2(100, 64)));
		dynamic_cast<SpinBoxForImage*>(spinBoxS_["�G���"].get())->AddData(enemyH_[EnemyType::Circle]);
		

		spinBoxS_ = std::make_unique<SpinBoxForString>(VECTOR2(basePosX + (bSize + bSpace)*2, bSpace * 3), 100,CreateFontToHandle(NULL,30,1));
		spinBoxS_->AddData("aaa");
		spinBoxS_->AddData("bbb");
		list_.resize(3);
		// �X�|�i�[�̐��\���p���X�g���쐬
		for (int w = 0; w < 3; w++)
		{
			for (int a = 0; a < spawners.size(); a++)
			{
				list_[w].emplace_back(std::make_unique<ImageList>(VECTOR2(SELECT_UI_POS.first.x + 5, SELECT_UI_POS.second.y / 1.5), VECTOR2((SELECT_UI_POS.second.x - SELECT_UI_POS.first.x - 10), (SELECT_UI_POS.second.y - SELECT_UI_POS.second.y / 3 - 50) / 2)));
			}
		}
		selSpawner_ = 0;
		selWave_ = 0;
		// �{�^���̍쐬
		if (spawners.size() == 2)
		{
			button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, bSpace * 2), VECTOR2(basePosY, bSize + bSpace * 2), VECTOR2(10, 10), 0xff0000, [&]() {selSpawner_ = 0; return true; }, VECTOR2()));
			buttonText_.emplace_back(ButtonText{ "�X�|�i�[1",0xffffff,VECTOR2(basePosX,  bSpace * 2 - GetFontSize()) });
		
			button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace), bSpace * 2), VECTOR2(basePosY + (bSize + bSpace), bSize + bSpace * 2), VECTOR2(10, 10), 0xffffff, [&]() {selSpawner_ = 1; return true; }, VECTOR2()));
			buttonText_.emplace_back(ButtonText{ "�X�|�i�[2", 0xffffff, VECTOR2(basePosX + (bSize + bSpace), bSpace * 2 - GetFontSize()) });

			button_.emplace_back(std::make_unique<ImageRectButton>(VECTOR2(basePosX, bSpace + (bSize + bSpace * 2)), VECTOR2(64,64), L"./data/image/circle.png", L"data/image/circle.png", [&]() {list_[selWave_][selSpawner_]->Add(IMAGE_ID(L"data/image/circle.png")); return true; }, VECTOR2()));
			button_.emplace_back(std::make_unique<ImageRectButton>(VECTOR2(basePosX + (bSize + bSpace), bSpace + (bSize + bSpace * 2)), VECTOR2(64,64), L"./data/image/square.png", L"data/image/square.png", [&]() {list_[selWave_][selSpawner_]->Add(IMAGE_ID(L"data/image/square.png")); return true; }, VECTOR2()));
			button_.emplace_back(std::make_unique<ImageRectButton>(VECTOR2(basePosX + (bSize + bSpace) * 2, bSpace + (bSize + bSpace * 2)), VECTOR2(64,64), L"./data/image/triangle.png", L"data/image/triangle.png", [&]() {list_[selWave_][selSpawner_]->Add(IMAGE_ID(L"data/image/triangle.png")); return true; }, VECTOR2()));

			dynamic_cast<SpinBoxForInt*>(spinBoxS_["�X�|�i�["].get())->AddData(2);
			dynamic_cast<SpinBoxForInt*>(spinBoxS_["�X�|�i�["].get())->AddData(1);
		}
		else if(spawners.size()==1)
		{
			button_.emplace_back(std::make_unique<ImageRectButton>(VECTOR2(basePosX, bSpace + (bSize + bSpace * 2)), VECTOR2(64, 64), L"./data/image/circle.png", L"data/image/circle.png", [&]() {list_[selWave_][selSpawner_]->Add(IMAGE_ID(L"data/image/circle.png")); return true; }, VECTOR2()));
			button_.emplace_back(std::make_unique<ImageRectButton>(VECTOR2(basePosX + (bSize + bSpace), bSpace + (bSize + bSpace * 2)), VECTOR2(64, 64), L"./data/image/square.png", L"data/image/square.png", [&]() {list_[selWave_][selSpawner_]->Add(IMAGE_ID(L"data/image/square.png")); return true; }, VECTOR2()));
			button_.emplace_back(std::make_unique<ImageRectButton>(VECTOR2(basePosX + (bSize + bSpace) * 2, bSpace + (bSize + bSpace * 2)), VECTOR2(64, 64), L"./data/image/triangle.png", L"data/image/triangle.png", [&]() {list_[selWave_][selSpawner_]->Add(IMAGE_ID(L"data/image/triangle.png")); return true; }, VECTOR2()));
			dynamic_cast<SpinBoxForInt*>(spinBoxS_["�X�|�i�["].get())->AddData(1);

		}
		else
		{
			// �G���[
		}
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, (strSize.y + bSpace) * 6) + strSize, VECTOR2(bSize,bSize/2), VECTOR2(10,10), 0xffffff, [&]() {
			list_[selWave_][selSpawner_]
				->Add(dynamic_cast<SpinBoxForImage*>(spinBoxS_["�G���"].get())->GetSelData());
			spawnTime = GetKeyInputNumberToFloat(keyInputHandleForSpawnTime);
			return true; }, VECTOR2()));
		button_.back()->SetString("�o�^",VECTOR2(15,10));
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX-strSize.x/2, (strSize.y + bSpace) * 6) + strSize, VECTOR2(bSize, bSize / 2), VECTOR2(10, 10), 0xffffff, [&]() {
			list_[selWave_][selSpawner_]->Del();
			return true;
			}, VECTOR2()));
		button_.back()->SetString("�߂�", VECTOR2(15, 10));
		for (auto&& list : button_)
		{
			list->SetAuto();
		}
		std::vector<RootDir> root;
		if (mainStay.size() != 0 && spawners.size() != 0)
		{
			root = astar_->AstarStart(scene->cusMap_->PosFromIndex(mainStay[0]),
							   scene->cusMap_->PosFromIndex(spawners[0]));
		}
		spawner_= spawners;
		// ���͏�Ԃ̏�����
		keyInputHandleForSpawnTime = MakeKeyInput(5, true, true, true,0,1);
		SetActiveKeyInput(keyInputHandleForSpawnTime);
		SetKeyInputNumber(0, keyInputHandleForSpawnTime);
		SetKeyInputStringFont(fontHandle_);
		return true;
	}
	void Update(CustomMapScene* scene)
	{
		selSpawner_= dynamic_cast<SpinBoxForInt*>(spinBoxS_["�X�|�i�["].get())->GetSelData()-1;
		selWave_= dynamic_cast<SpinBoxForInt*>(spinBoxS_["Wave"].get())->GetSelData()-1;
		list_[selWave_][selSpawner_]->Update();
		if (lpMouseController.IsHitBoxToMouse(VECTOR2(), VECTOR2(SELECT_UI_POS.first.x, TEXT_UI_POS.first.y)))
		{
			lpApplication.GetCamera().ScaleLock(false);
		}
		else
		{
			lpApplication.GetCamera().ScaleLock(true);
		}
		for (auto&& list : button_)
		{
			if (list->Update())
			{
				break;
			}
		}
		spinBoxS_->Update();
		for (auto&& map : spinBoxS_)
		{
			map.second->Update();
		}
	};

	void Draw(CustomMapScene* scene)
	{
		// �g�\��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawRoundRect(SELECT_UI_POS.first.x, SELECT_UI_POS.first.y, SELECT_UI_POS.second.x, SELECT_UI_POS.second.y, 20, 20, 0x555555, true);
		DrawRoundRect(SELECT_UI_POS.first.x, SELECT_UI_POS.first.y, SELECT_UI_POS.second.x, SELECT_UI_POS.second.y, 20, 20, 0xffffff, false);
		DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0x555555, true);
		DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0xffffff, false);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
		// �������̕\��

		for (auto&& list : button_)
		{
			list->Draw();
		}
		for (auto&& list : buttonText_)
		{
			DrawString(list.pos_.x, list.pos_.y, _StW(list.str_).c_str(), list.color_);
		}
		list_[selWave_][selSpawner_]->Draw();
		spinBoxS_->Draw();
		const int bSize = 64;
		const int bSpace = 10;
		const int basePosX = SELECT_UI_POS.first.x + bSpace;
		const int basePosY = SELECT_UI_POS.first.x + bSize + bSpace;

		for (auto&& map : spinBoxS_)
		{
			DrawStringToHandle(basePosX, map.second->GetPos().y+(map.second->GetSize().y/2-GetFontSizeToHandle(fontHandle_)/2), _StW(map.first).c_str(), 0xffffff, fontHandle_);
			map.second->Draw();
		}
		DrawStringToHandle(basePosX, (bSize + bSpace) * 3 - 5, L"�o������", 0xffffff, fontHandle_);
		DrawBox(basePosX-2+ GetDrawStringWidthToHandle(L"�X�|�i�[ ", GetStringLength(L"�X�|�i�[ "), fontHandle_), (bSize + bSpace) * 3-5, basePosX + 100+ GetDrawStringWidthToHandle(L"�X�|�i�[ ", GetStringLength(L"�X�|�i�[ "), fontHandle_), (bSize + bSpace) * 3 + GetFontSizeToHandle(fontHandle_)+5, 0x000000, true);
		DrawBox(basePosX-2+ GetDrawStringWidthToHandle(L"�X�|�i�[ ", GetStringLength(L"�X�|�i�[ "), fontHandle_), (bSize + bSpace) * 3-5, basePosX + 100+ GetDrawStringWidthToHandle(L"�X�|�i�[ ", GetStringLength(L"�X�|�i�[ "), fontHandle_), (bSize + bSpace) * 3 + GetFontSizeToHandle(fontHandle_)+5, 0xffffff, false);
		if (DrawKeyInputString(basePosX + GetDrawStringWidthToHandle(L"�X�|�i�[ ", GetStringLength(L"�X�|�i�[ "), fontHandle_), (bSize + bSpace) * 3, keyInputHandleForSpawnTime)==-1)
		{
			DrawString(basePosX - 2 + GetDrawStringWidthToHandle(L"�X�|�i�[ ", GetStringLength(L"�X�|�i�[ "), fontHandle_), (bSize + bSpace) * 3, std::to_wstring(spawnTime).c_str(), 0xffffff);
		}
		DrawString(basePosX - 2 + GetDrawStringWidthToHandle(L"�X�|�i�[ ", GetStringLength(L"�X�|�i�[ "), fontHandle_), (bSize + bSpace) * 4, std::to_wstring(spawnTime).c_str(), 0xffffff);

	}
	void Delete() {
		DeleteKeyInput(keyInputHandleForSpawnTime);
	}
private:
	// Astar�N���X�̃|�C���^�[
	std::unique_ptr<Astar>astar_;
	std::vector<int>spawner_;

	//EnemyType selEnemy_;

	std::list<std::unique_ptr<Button>>button_;
	std::list<ButtonText>buttonText_;
	// �G���[�i���o�[
	int errorNum_;
	// �G���[���e
	// �ő�񐔁i���{��S�p��16�����j
	// �ő�s���i6�s�j
	std::vector<std::string> errorText_;
	std::vector<std::vector<std::unique_ptr<ImageList>>>list_;
	int selSpawner_;
	int selWave_;
	
	std::unique_ptr<SpinBoxForString>spinBoxS_;
	std::map<EnemyType, int>enemyH_;
	std::map<std::string,std::unique_ptr<SpinBox>>spinBoxS_;
	int fontHandle_;

	// ���l���͗p
	int keyInputHandleForSpawnTime;
	float spawnTime;
};