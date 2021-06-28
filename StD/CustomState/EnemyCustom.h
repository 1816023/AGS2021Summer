#pragma once
#include "CustomState.h"
//#include "../Unit/Enemy/EnemyType.h"
#include "../Scene/CustomMapScene.h"
//#include "../Unit/Enemy/Enemy.h"

#define CUSTOM dynamic_cast<Custom*>(scene->map_.get())

struct EnemyCustom :public CustomStateBase
{
	EnemyCustom(){};
	~EnemyCustom() {};
	bool Init(CustomMapScene* scene)
	{
		astar_ = std::make_unique<Astar>(*scene->cusMap_);
		const auto& spawners = scene->cusMap_->Getspawner();
		const auto& mainStay = scene->cusMap_->GetMainStay();
		if (mainStay.size() != 0 && spawners.size() != 0)
		{
			astar_->AstarStart(mainStay.at(1), spawners.at(0));
		}
		spawner_= scene->cusMap_->Getspawner();
		return true;
	}
	void Update(CustomMapScene* scene)
	{

	}

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

	}
	void Delete() {
	}
	// Astarクラスのポインター
	std::unique_ptr<Astar>astar_;
	std::map<int, VECTOR2>spawner_;

	//EnemyType selEnemy_;

	std::list<std::unique_ptr<Button>>button_;
	std::list<ButtonText>buttonText_;
	// エラーナンバー
	int errorNum_;
	// エラー内容
	// 最大列数（日本語全角で16文字）
	// 最大行数（6行）
	std::vector<std::string> errorText_;

};