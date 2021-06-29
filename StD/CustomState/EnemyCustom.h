#pragma once
#include "CustomState.h"
#include "../Scene/CustomMapScene.h"
#include "../ScrollList.h"
#define CUSTOM dynamic_cast<Custom*>(scene->map_.get())

struct EnemyCustom :public CustomStateBase
{
	EnemyCustom(){};
	~EnemyCustom() {};
	bool Init(CustomMapScene* scene)
	{
		const int bSize = 64;
		const int bSpace = 20;
		const int basePosX = SELECT_UI_POS.first.x + bSpace;
		const int basePosY = SELECT_UI_POS.first.x + bSize + bSpace;
		astar_ = std::make_unique<Astar>(*scene->cusMap_);
		const auto& spawners = scene->cusMap_->GetSpawner();
		const auto& mainStay = scene->cusMap_->GetMainStay();
		// ボタンの作成
		if (spawners.size() == 2)
		{
			button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, bSpace * 2), VECTOR2(basePosY, bSize + bSpace * 2), VECTOR2(10, 10), 0xff0000, [&]() { return true; }, VECTOR2()));
			buttonText_.emplace_back(ButtonText{ "スポナー1",0xffffff,VECTOR2(basePosX,  bSpace * 2 - GetFontSize()) });
		
			button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace), bSpace * 2), VECTOR2(basePosY + (bSize + bSpace), bSize + bSpace * 2), VECTOR2(10, 10), 0xffffff, [&]() {return true; }, VECTOR2()));
			buttonText_.emplace_back(ButtonText{ "スポナー2", 0xffffff, VECTOR2(basePosX + (bSize + bSpace), bSpace * 2 - GetFontSize()) });

		}
		else if(spawners.size()==1)
		{
			
		}
		else
		{
			// エラー
		}

		
		if (mainStay.size() != 0 && spawners.size() != 0)
		{

			astar_->AstarStart(scene->cusMap_->PosFromIndex(mainStay[0]),
							   scene->cusMap_->PosFromIndex(spawners[0]));
		}
		list_ = std::make_unique<ScrollList>(VECTOR2(SELECT_UI_POS.first.x+5,SELECT_UI_POS.second.y/1.5), VECTOR2((SELECT_UI_POS.second.x-SELECT_UI_POS.first.x-10), (SELECT_UI_POS.second.y- SELECT_UI_POS.second.y /3-50)/2), ListType::STRING);
		list_->Add(StringState{ "草草草",0xffffff });
		list_->Add(StringState{ "草草草",0xff0000 });
		spawner_= spawners;
		return true;
	}
	void Update(CustomMapScene* scene)
	{
		list_->Update();
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
			list->Update();
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
		list_->Draw();
	}
	void Delete() {
	}
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
	std::unique_ptr<ScrollList> list_;

};