#pragma once
#include "CustomState.h"
#include "../Scene/CustomMapScene.h"
#include "../GUI/ScrollList/ImageList.h"
#include "../GUI/ScrollList/StringList.h"
#include "../GUI/Button/ImageRectButton.h"
#include "../Mng/ImageMng.h"
#include "../Mng/ImageMng.h"
#include "../GUI/SpinBox/SpinBoxForInt.h"
#include "../GUI/SpinBox/SpinBoxForImage.h"
#define CUSTOM dynamic_cast<Custom*>(scene->map_.get())

struct EnemyCustom :public CustomStateBase
{
	EnemyCustom(){};
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
		auto strSize=VECTOR2(GetDrawStringWidthToHandle(L"スポナー ",GetStringLength(L"スポナー "), fontHandle_),GetFontSizeToHandle(fontHandle_));
		spinBoxS_.try_emplace("スポナー", std::make_unique<SpinBoxForInt>(VECTOR2(basePosX,0 )+strSize, 100, fontHandle_));
		spinBoxS_.try_emplace("Wave", std::make_unique<SpinBoxForInt>(VECTOR2(basePosX, strSize.y+bSpace) + strSize, 100, fontHandle_));
		dynamic_cast<SpinBoxForInt*>(spinBoxS_["Wave"].get())->AddData(3);
		dynamic_cast<SpinBoxForInt*>(spinBoxS_["Wave"].get())->AddData(2);
		dynamic_cast<SpinBoxForInt*>(spinBoxS_["Wave"].get())->AddData(1);
		spinBoxS_.try_emplace("ルート", std::make_unique<SpinBoxForInt>(VECTOR2(basePosX, (strSize.y + bSpace)*2) + strSize, 100, fontHandle_));
		dynamic_cast<SpinBoxForInt*>(spinBoxS_["ルート"].get())->AddData(1);
		spinBoxS_.try_emplace("敵種類", std::make_unique<SpinBoxForImage>(VECTOR2(basePosX, (strSize.y + bSpace) * 3) + strSize, VECTOR2(100, 64)));
		dynamic_cast<SpinBoxForImage*>(spinBoxS_["敵種類"].get())->AddData(enemyH_[EnemyType::Circle]);
		

		list_.resize(3);
		// スポナーの数表示用リストを作成
		for (int w = 0; w < 3; w++)
		{
			for (int a = 0; a < spawners.size(); a++)
			{
				list_[w].emplace_back(std::make_unique<ImageList>(VECTOR2(SELECT_UI_POS.first.x + 5, SELECT_UI_POS.second.y / 1.5), VECTOR2((SELECT_UI_POS.second.x - SELECT_UI_POS.first.x - 10), (SELECT_UI_POS.second.y - SELECT_UI_POS.second.y / 3 - 50) / 2)));
			}
		}
		selSpawner_ = 0;
		selWave_ = 0;
		if (spawners.size() == 2)
		{
			dynamic_cast<SpinBoxForInt*>(spinBoxS_["スポナー"].get())->AddData(2);
			dynamic_cast<SpinBoxForInt*>(spinBoxS_["スポナー"].get())->AddData(1);
		}
		else if(spawners.size()==1)
		{
			dynamic_cast<SpinBoxForInt*>(spinBoxS_["スポナー"].get())->AddData(1);

		}
		else
		{
			// エラー
		}
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, (strSize.y + bSpace) * 6) + strSize, VECTOR2(bSize,bSize/2), VECTOR2(10,10), 0xffffff, [&]() {
			list_[selWave_][selSpawner_]
				->Add(dynamic_cast<SpinBoxForImage*>(spinBoxS_["敵種類"].get())->GetSelData());
			spawnTime = GetKeyInputNumberToFloat(keyInputHandleForSpawnTime);
			return true; }, VECTOR2()));
		button_.back()->SetString("登録",VECTOR2(15,10));
		button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX-strSize.x/2, (strSize.y + bSpace) * 6) + strSize, VECTOR2(bSize, bSize / 2), VECTOR2(10, 10), 0xffffff, [&]() {
			list_[selWave_][selSpawner_]->Del();
			return true;
			}, VECTOR2()));
		button_.back()->SetString("戻す", VECTOR2(15, 10));
		for (auto&& list : button_)
		{
			list->SetAuto();
		}
		if (mainStay.size() != 0 && spawners.size() != 0)
		{
			astar_->AstarStart(scene->cusMap_->PosFromIndex(mainStay[0]),
							   scene->cusMap_->PosFromIndex(spawners[0]));
		}
		spawner_= spawners;
		// 入力状態の初期化
		keyInputHandleForSpawnTime = MakeKeyInput(5, true, true, true,0,1);
		SetActiveKeyInput(keyInputHandleForSpawnTime);
		SetKeyInputNumber(0, keyInputHandleForSpawnTime);
		SetKeyInputStringFont(fontHandle_);
		return true;
	}
	void Update(CustomMapScene* scene)
	{
		selSpawner_= dynamic_cast<SpinBoxForInt*>(spinBoxS_["スポナー"].get())->GetSelData()-1;
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
		for (auto&& map : spinBoxS_)
		{
			map.second->Update();
		}
	};

	void Draw(CustomMapScene* scene)
	{
		// 枠表示
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawRoundRect(SELECT_UI_POS.first.x, SELECT_UI_POS.first.y, SELECT_UI_POS.second.x, SELECT_UI_POS.second.y, 20, 20, 0x555555, true);
		DrawRoundRect(SELECT_UI_POS.first.x, SELECT_UI_POS.first.y, SELECT_UI_POS.second.x, SELECT_UI_POS.second.y, 20, 20, 0xffffff, false);
		DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0x555555, true);
		DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0xffffff, false);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
		// 説明文の表示

		for (auto&& list : button_)
		{
			list->Draw();
		}
		for (auto&& list : buttonText_)
		{
			DrawString(list.pos_.x, list.pos_.y, _StW(list.str_).c_str(), list.color_);
		}
		list_[selWave_][selSpawner_]->Draw();
		const int bSize = 64;
		const int bSpace = 10;
		const int basePosX = SELECT_UI_POS.first.x + bSpace;
		const int basePosY = SELECT_UI_POS.first.x + bSize + bSpace;

		for (auto&& map : spinBoxS_)
		{
			DrawStringToHandle(basePosX, map.second->GetPos().y+(map.second->GetSize().y/2-GetFontSizeToHandle(fontHandle_)/2), _StW(map.first).c_str(), 0xffffff, fontHandle_);
			map.second->Draw();
		}
		DrawStringToHandle(basePosX, (bSize + bSpace) * 3 - 5, L"出現時間", 0xffffff, fontHandle_);
		DrawBox(basePosX-2+ GetDrawStringWidthToHandle(L"スポナー ", GetStringLength(L"スポナー "), fontHandle_), (bSize + bSpace) * 3-5, basePosX + 100+ GetDrawStringWidthToHandle(L"スポナー ", GetStringLength(L"スポナー "), fontHandle_), (bSize + bSpace) * 3 + GetFontSizeToHandle(fontHandle_)+5, 0x000000, true);
		DrawBox(basePosX-2+ GetDrawStringWidthToHandle(L"スポナー ", GetStringLength(L"スポナー "), fontHandle_), (bSize + bSpace) * 3-5, basePosX + 100+ GetDrawStringWidthToHandle(L"スポナー ", GetStringLength(L"スポナー "), fontHandle_), (bSize + bSpace) * 3 + GetFontSizeToHandle(fontHandle_)+5, 0xffffff, false);
		if (DrawKeyInputString(basePosX + GetDrawStringWidthToHandle(L"スポナー ", GetStringLength(L"スポナー "), fontHandle_), (bSize + bSpace) * 3, keyInputHandleForSpawnTime)==-1)
		{
			DrawString(basePosX - 2 + GetDrawStringWidthToHandle(L"スポナー ", GetStringLength(L"スポナー "), fontHandle_), (bSize + bSpace) * 3, std::to_wstring(spawnTime).c_str(), 0xffffff);
		}
		DrawString(basePosX - 2 + GetDrawStringWidthToHandle(L"スポナー ", GetStringLength(L"スポナー "), fontHandle_), (bSize + bSpace) * 4, std::to_wstring(spawnTime).c_str(), 0xffffff);

	}
	void Delete() {
		DeleteKeyInput(keyInputHandleForSpawnTime);
	}
private:
	// Astarクラスのポインター
	std::unique_ptr<Astar>astar_;
	std::vector<int>spawner_;

	//EnemyType selEnemy_;

	std::list<std::unique_ptr<Button>>button_;
	std::list<ButtonText>buttonText_;
	// エラーナンバー
	int errorNum_;
	// エラー内容
	// 最大列数（日本語全角で16文字）
	// 最大行数（6行）
	std::vector<std::string> errorText_;
	std::vector<std::vector<std::unique_ptr<ImageList>>>list_;
	int selSpawner_;
	int selWave_;
	std::map<EnemyType, int>enemyH_;
	std::map<std::string,std::unique_ptr<SpinBox>>spinBoxS_;
	int fontHandle_;

	// 数値入力用
	int keyInputHandleForSpawnTime;
	float spawnTime;
};