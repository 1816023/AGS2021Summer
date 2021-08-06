#pragma once
#include "CustomState.h"
#include "../Scene/CustomMapScene.h"
#include "../GUI/ScrollList/ImgeAndStringList.h"
#include "../GUI/Button/ImageRectButton.h"
#include "../GUI/SpinBox/SpinBoxForString.h"
#include "../GUI/SpinBox/SpinBoxForInt.h"
#include "../GUI/SpinBox/SpinBoxForImage.h"
#include "../GUI/Canvas.h"
#include "../Mng/FontMng.h"
#include "../Mng/ImageMng.h"
#include "../StringUtil.h"

#define CUSTOM dynamic_cast<Custom*>(scene->map_.get())

struct EnemyCustom : public CustomStateBase
{
	EnemyCustom(){};
	~EnemyCustom() {};
	bool Init(CustomMapScene* scene)
	{
		scene->canvas_->ClearUI();
		const int bSize = 64;
		const int bSpace = 10;
		const int basePosX = SELECT_UI_POS.first.x + bSpace;
		const int basePosY = SELECT_UI_POS.first.x + bSize + bSpace;
		enemyH_.try_emplace(EnemyType::Circle, IMAGE_ID(L"./data/image/circle.png"));
		enemyH_.try_emplace(EnemyType::Pentagon, IMAGE_ID(L"./data/image/pentagon.png"));
		enemyH_.try_emplace(EnemyType::Square, IMAGE_ID(L"./data/image/square.png"));
		enemyH_.try_emplace(EnemyType::Triangle, IMAGE_ID(L"./data/image/triangle.png"));
		astar_ = std::make_unique<Astar>(*scene->cusMap_);
		const auto& spawners = scene->cusMap_->GetSpawner();
		const auto& mainStay = scene->cusMap_->GetMainStay();
		// root�̐ݒ�
		std::vector<std::vector<RootDir>> root;
		if (mainStay.size() != 0 && spawners.size() != 0)
		{
			for (int s = 0; s < spawners.size(); s++)
			{
				for (int m = 0; m < mainStay.size(); m++)
				{
					root.push_back(astar_->AstarStart(scene->cusMap_->PosFromIndex(spawners[s]),
						scene->cusMap_->PosFromIndex(mainStay[m])));
				}
			}
		}
		scene->cusMap_->SetRoot(root);
		
		spawner_ = spawners;

		fontHandle_ = lpFontMng.AddStrFont(30, L"enemyUI");
		// UI�̏�����
		auto strSize=VECTOR2(GetDrawStringWidthToHandle(L"�X�|�i�[ ",GetStringLength(L"�X�|�i�[ "), fontHandle_),GetFontSizeToHandle(fontHandle_));
		// �X�|�i�[�X�s���{�b�N�X�̐ݒ�
		std::map<std::string, SpinBox*>spinBoxS;
		spinBoxS.try_emplace("�X�|�i�[", new SpinBoxForInt(VECTOR2(bSpace,0 )+strSize, 100, scene->canvas_->GetPos(), fontHandle_));
		for (int s = spawners.size(); s > 0; s--)
		{
			dynamic_cast<SpinBoxForInt*>(spinBoxS["�X�|�i�["])->AddData(s);
		}
		// �E�F�[�u�̃X�s���{�b�N�X�̐ݒ�
		spinBoxS.try_emplace("Wave", new SpinBoxForInt(VECTOR2(bSpace, strSize.y+bSpace) + strSize, 100, scene->canvas_->GetPos(), fontHandle_));
		dynamic_cast<SpinBoxForInt*>(spinBoxS["Wave"])->AddData(3);
		dynamic_cast<SpinBoxForInt*>(spinBoxS["Wave"])->AddData(2);
		dynamic_cast<SpinBoxForInt*>(spinBoxS["Wave"])->AddData(1);
		// ���[�g�̃X�s���{�b�N�X�̐ݒ�
		spinBoxS.try_emplace("���[�g",new SpinBoxForInt(VECTOR2(bSpace, (strSize.y + bSpace)*2) + strSize, 100, scene->canvas_->GetPos(), fontHandle_));
		for (int r = root.size()-1; r > -1; r--)
		{
			dynamic_cast<SpinBoxForInt*>(spinBoxS["���[�g"])->AddData(r);
		}
		// �G��ނ̃X�s���{�b�N�X�̐ݒ�
		spinBoxS.try_emplace("�G���", new SpinBoxForImage(VECTOR2(bSpace, (strSize.y + bSpace) * 3) + strSize, VECTOR2(100, 64), scene->canvas_->GetPos()));
		dynamic_cast<SpinBoxForImage*>(spinBoxS["�G���"])->AddData(enemyH_[EnemyType::Circle]);
		dynamic_cast<SpinBoxForImage*>(spinBoxS["�G���"])->AddData(enemyH_[EnemyType::Pentagon]);
		dynamic_cast<SpinBoxForImage*>(spinBoxS["�G���"])->AddData(enemyH_[EnemyType::Square]);
		dynamic_cast<SpinBoxForImage*>(spinBoxS["�G���"])->AddData(enemyH_[EnemyType::Triangle]);
		
		for (auto& box : spinBoxS)
		{
			scene->canvas_->AddUIByName(box.second,_StW(box.first));
		}


		list_.resize(3);
		// �X�|�i�[�̐��\���p���X�g���쐬
		for (int w = 0; w < 3; w++)
		{
			for (int a = 0; a < spawners.size(); a++)
			{
				list_[w].emplace_back(
					std::make_pair(
						std::make_unique<ImgeAndStringList>(VECTOR2(SELECT_UI_POS.first.x + 5, SELECT_UI_POS.second.y / 1.5), VECTOR2((SELECT_UI_POS.second.x - SELECT_UI_POS.first.x - 10), (SELECT_UI_POS.second.y - SELECT_UI_POS.second.y / 3 - 50) / 2))
						, std::vector<int>(0)
					)
				);
			}
		}
		selSpawner_ = 0;
		selWave_ = 0;
		// �{�^���̍쐬
		// �o�^�{�^��
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, (strSize.y + bSpace) * 6) + strSize, VECTOR2(bSize,bSize/2), VECTOR2(10,10), 0xffffff, [&,scene]() {
			auto typeBox = dynamic_cast<SpinBoxForImage*>(scene->canvas_->GetUIByName(L"�G���"))->GetSelData();
			auto rootBox = dynamic_cast<SpinBoxForImage*>(scene->canvas_->GetUIByName(L"���[�g"))->GetSelData();
			list_[selWave_][selSpawner_].first
				->Add(typeBox,std::to_string(GetKeyInputNumberToFloat(keyInputHandleForSpawnTime)));
			list_[selWave_][selSpawner_].second.push_back(rootBox);
				spawnTime = GetKeyInputNumberToFloat(keyInputHandleForSpawnTime);
			return true; }));
		button_.back()->SetString("�o�^",VECTOR2(15,10));
		// �߂��{�^��
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX-strSize.x/2, (strSize.y + bSpace) * 6) + strSize, VECTOR2(bSize, bSize / 2), VECTOR2(10, 10), 0xffffff, [&]() {
			list_[selWave_][selSpawner_].first->Del();
			if (list_[selWave_][selSpawner_].second.size() != 0)
			{
				list_[selWave_][selSpawner_].second.pop_back();
			}
			return true;
			}));
		button_.back()->SetString("�߂�", VECTOR2(15, 10));
		// �ۑ��{�^��
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX - strSize.x , (strSize.y + bSpace) * 6) + strSize, VECTOR2(bSize, bSize / 2), VECTOR2(10, 10), 0xffffff, [&,scene]() {
			auto error=scene->cusMap_->SaveFile(spawners.size(),list_);
			return error==0;
			}));
		button_.back()->SetString("Save", VECTOR2(15, 10));
		// �{�^���̎����X�V
		for (auto&& list : button_)
		{
			list->SetAuto();
		}

		// ���͏�Ԃ̏�����
		keyInputHandleForSpawnTime = MakeKeyInput(5, true, true, true,0,1);
		SetActiveKeyInput(keyInputHandleForSpawnTime);
		SetKeyInputNumber(0, keyInputHandleForSpawnTime);
		SetKeyInputStringFont(fontHandle_);
		return true;
	}
	void Update(CustomMapScene* scene)
	{
		selSpawner_= dynamic_cast<SpinBoxForInt*>(scene->canvas_->GetUIByName(L"�X�|�i�["))->GetSelData()-1;
		selWave_= dynamic_cast<SpinBoxForInt*>(scene->canvas_->GetUIByName(L"Wave"))->GetSelData()-1;
		list_[selWave_][selSpawner_].first->Update();
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
	/*	for (auto&& map : spinBoxS_)
		{
			map.second->Update();
		}*/
	};

	void DrawUI(CustomMapScene* scene)
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
		list_[selWave_][selSpawner_].first->Draw();
		const int bSize = 64;
		const int bSpace = 10;
		const int basePosX = SELECT_UI_POS.first.x + bSpace;
		const int basePosY = SELECT_UI_POS.first.x + bSize + bSpace;

		/*for (auto&& map : spinBoxS_)
		{
			DrawStringToHandle(basePosX, map.second->GetPos().y+(map.second->GetSize().y/2-GetFontSizeToHandle(fontHandle_)/2), _StW(map.first).c_str(), 0xffffff, fontHandle_);
			map.second->Draw();
		}*/
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
	// �Z�[�u�p
	// �G���[�Ԃ�
	int Save(std::string filename)
	{
		//���̌`�ŕۑ�
		// <wave id = "">
		//	<spawner id = "">
		//		<enemy type = "" time = "" root = "" / >
		//		<enemy type = "" time = "" root = "" / >
		//	</spawner>
		// </wave>
		using namespace tinyxml2;
		tinyxml2::XMLDocument doc;
		auto error=doc.LoadFile(filename.c_str());
		if (error != XML_SUCCESS)
		{
			// �t�@�C���I�[�v���G���[
			return 1;
		}
		tinyxml2::XMLElement* elm = doc.FirstChildElement("spawn");
		// �w�肵���G�������g��"id"�A�g���r���[�g���w�肳�ꂽ���̂ɂȂ�܂ŌZ���T���ɍs��
		// �T���o�����true�@
		// ������Ȃ�������false
		std::function<bool(tinyxml2::XMLElement*, int)> check = [&](tinyxml2::XMLElement* elm, int num) {
			if (elm->IntAttribute("id") != num)
			{
				elm = elm->NextSiblingElement();
				if (!elm)
				{
					return false;
				}
				check(elm, num);
			}
			return true;
		};
		std::map<int, EnemyType>enemyID = {
			{IMAGE_ID(L"./data/image/circle.png"),EnemyType::Circle},
			{IMAGE_ID(L"./data/image/square.png"),EnemyType::Square},
			{IMAGE_ID(L"./data/image/pentagon.png"),EnemyType::Pentagon},
			{IMAGE_ID(L"./data/image/triangle.png"),EnemyType::Triangle},

		};
		/////
		// �E�F�[�u�̐���
		for (int w = 0; w < 3; w++)
		{
			// �h�L�������g����wave�̃G�������g���擾����
			tinyxml2::XMLElement* wave = doc.FirstChildElement("wave");
			if (!wave)
			{
				return 1;
			}
			// �擾�����G�������g���w�肵��ID�������̂ɂȂ�܂ōċA����
			if (check(wave, w))
			{
				// �X�|�i�[�̐�������
				for (int s=0;s< spawner_.size();s++)
				{
					// ���X�g�̎擾
					auto& enemyList = list_[w][s].first->GetList();
					// �X�|�i�[�̃G�������g�쐬
					tinyxml2::XMLElement* spawner = wave->InsertNewChildElement("spawner");
					// �X�|�i�[��ID��ݒ�
					spawner->SetAttribute("id", s);
					int cnt = 0;
					// ���X�g�̂Ł[�������ƂɃX�|�i�[�G�������g�ɒǉ����Ă���
					for (auto& list : enemyList)
					{
						// �V����enemy�Ƃ����G�������g���쐬����
						tinyxml2::XMLElement* element = doc.NewElement("enemy");
						// �X�|�i�[�̎q���̌��ɍ쐬����enemy�G�������g��ǉ�����
						spawner->InsertEndChild(element);
						// �G�l�~�[��type,time,root�̃A�g���r���[�g��ǉ�����
						element->SetAttribute("type", static_cast<int>(enemyID[list.handle]));
						element->SetAttribute("time", list.str.c_str());
						element->SetAttribute("root", list_[w][s].second[cnt++]);
					}
				}
			}

		}
		doc.SaveFile(filename.c_str());
		return true;
	}

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

	std::vector<std::vector<std::pair<std::unique_ptr<ImgeAndStringList>,std::vector<int>>>>list_;
	int selSpawner_;
	int selWave_;
	
	std::map<EnemyType, int>enemyH_;
//	std::map<std::string,SpinBox*>spinBoxS_;
	int fontHandle_;

	// ���l���͗p
	int keyInputHandleForSpawnTime;
	float spawnTime;
};