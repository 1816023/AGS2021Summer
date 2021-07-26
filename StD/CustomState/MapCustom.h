#pragma once
#include "../Scene/CustomMapScene.h"
#include "CustomState.h"
#include "../StringUtil.h"
#include "../Map/Astar.h"
#include "../MapEnum.h"
#include "../CustumErrorText.h"
#include "../GUI/Canvas.h"
#include "../GUI/UIText.h"

struct MapCustom:public CustomStateBase
{

	MapCustom() {};
	~MapCustom() {}
	bool Init(CustomMapScene* scene)override
	{		
		scene_ = scene;
		scene->canvas_->SetActive(true);
		errorText_ = std::make_unique<CustumErrorText>();
		const int bSize = 64;
		const int bSpace = 20;
		std::list<Button*>button;
		std::list<UIText*>buttonText;
		// ボタンの作成
		button.emplace_back(new RoundRectButton(VECTOR2(bSpace, bSpace * 2), VECTOR2(bSize, bSize), VECTOR2(10, 10), 0x007fff, [&]() {selChip_ = MapChipName::MAINSTAY; return true; }, VECTOR2()));
		buttonText.emplace_back(new UIText(VECTOR2(bSpace, bSpace * 2 - GetFontSize()), L"自拠点"));
		button.emplace_back(new RoundRectButton(VECTOR2(bSize + bSpace * 2, bSpace * 2), VECTOR2(bSize, bSize), VECTOR2(10, 10), 0xff0f0f, [&]() {selChip_ = MapChipName::SPAWNER; return true; }, VECTOR2()));
		buttonText.emplace_back(new UIText(VECTOR2(bSize + bSpace * 2, bSpace * 2 - GetFontSize()), L"敵出現"));
		button.emplace_back(new RoundRectButton(VECTOR2(bSize * 2 + bSpace * 3, bSpace * 2), VECTOR2(bSize, bSize), VECTOR2(10, 10), 0xfff00, [&]() {selChip_ = MapChipName::ROOT; return true; }, VECTOR2()));
		buttonText.emplace_back(new UIText(VECTOR2(bSize * 2 + bSpace * 3, bSpace * 2 - GetFontSize()), L"敵侵攻"));
		button.emplace_back(new RoundRectButton(VECTOR2(bSpace, bSize + bSpace * 3), VECTOR2(bSize, bSize), VECTOR2(10, 10), 0xe3e3e3, [&]() {selChip_ = MapChipName::FIELD; return true; }, VECTOR2()));
		buttonText.emplace_back(new UIText(VECTOR2(bSpace, bSize + bSpace * 3 - GetFontSize()), L"自機配置"));
		button.emplace_back(new RoundRectButton(VECTOR2(bSize + bSpace * 2, bSize + bSpace * 3), VECTOR2(bSize, bSize), VECTOR2(10, 10), 0x333333, [&]() {selChip_ = MapChipName::WALL; return true; }, VECTOR2()));
		buttonText.emplace_back(new UIText(VECTOR2(bSize + bSpace * 2, bSize + bSpace * 3 - GetFontSize()), L"設置不可"));
		button.emplace_back(new RoundRectButton(VECTOR2(bSize * 2+ bSpace * 3,bSize + bSpace * 3), VECTOR2(bSize, bSize), VECTOR2(10, 10), 0xffffff, [&]() {selChip_ = MapChipName::MAX; return true; }, VECTOR2()));
		buttonText.emplace_back(new UIText(VECTOR2(bSize * 2 + bSpace * 3, bSize + bSpace * 3 - GetFontSize()), L"選択解除"));
		// システム系のボタン
		button.emplace_back(new RoundRectButton(VECTOR2(bSpace, SELECT_UI_POS.second.y - bSize / 2 - bSpace), VECTOR2(bSize, bSize/2), VECTOR2(10, 10), 0xffffff, std::bind(&MapCustom::Back, this), VECTOR2()));
		button.back()->SetString("Back", VECTOR2(bSize / 2 - GetDrawStringWidth(L"Back", GetStringLength(L"Back")) / 2, bSize / 4 - GetFontSize() / 2));
		button.emplace_back(new RoundRectButton(VECTOR2(bSpace * 2 + bSize, SELECT_UI_POS.second.y - bSize / 2 - bSpace), VECTOR2(bSize, bSize/2), VECTOR2(10, 10), 0xffffff, std::bind(&MapCustom::Next, this), VECTOR2()));
		button.back()->SetString("Next", VECTOR2(bSize / 2 - GetDrawStringWidth(L"Next", GetStringLength(L"Next")) / 2, bSize / 4 - GetFontSize() / 2));
		button.emplace_back(new RoundRectButton(VECTOR2(bSpace * 3 + bSize * 2, SELECT_UI_POS.second.y - bSize / 2 - bSpace), VECTOR2(bSize, bSize/2), VECTOR2(10, 10), 0xffffff, [&,scene]() {
			errorNum_ = static_cast<int>(scene->SaveCheck());
			if (static_cast<ErrorCode>(errorNum_) == ErrorCode::NoError)
			{
				scene->cusMap_->SaveFile(); 
				return  true; 
			}
			else
			{
				return false;
			}
			}, VECTOR2()));
		button.back()->SetString("Save", VECTOR2(bSize / 2 - GetDrawStringWidth(L"Save", GetStringLength(L"Save")) / 2, bSize / 4 - GetFontSize() / 2));
		
		// 全てのボタンを自動化する
		int cnt = 0;
		for (auto& b : button)
		{
			b->SetAuto();
			scene->canvas_->AddUIByID(b, b->GetPos(), cnt++);
		}
		for (auto& t : buttonText)
		{
			scene->canvas_->AddUIByID(t, t->GetPos(), cnt++);
		}
		scene->blendAlpha_ = 256;
		selChip_ = MapChipName::MAX;
		scene->LoadText("map");
		errorNum_ = 0;
		// エラーの内容
		errorText_->AddErrorText("");
		errorText_->AddErrorText("拠点とスポナーの数が多すぎます。\n最大数は各2つまでです。");
		errorText_->AddErrorText("拠点の数が多すぎます。\n最大数は2つまでです。");
		errorText_->AddErrorText("スポナーの数が多すぎます。\n最大数は2つまでです。");
		
		return false;

	}
	void Update(CustomMapScene* scene)override
	{
		VECTOR2 mPos = lpMouseController.GetPos();
		VECTOR2 mcPos = lpMouseController.GetOffsetPos();
		if (lpMouseController.GetClicking(MOUSE_INPUT_LEFT))
		{
			if (mPos.x < SELECT_UI_POS.first.x)
			{
				scene->cusMap_->SetChip(mcPos, selChip_);
			}
		}
		scene->blendAlpha_ += 2;
	}

	void Draw(CustomMapScene* scene)override
	{
		// 枠表示
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0x555555, true);
		DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0xffffff, false);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
		// 説明文の表示
		DrawString(TEXT_UI_POS.first.x + 3, TEXT_UI_POS.first.y + (TEXT_UI_POS.second.y - TEXT_UI_POS.first.y) / 5, _StW(scene->textData_[selChip_]).c_str(), 0xffffff);
		VECTOR2 mPos = lpMouseController.GetPos();
		errorText_->DrawErrorText(SELECT_UI_POS.first.x + 10, SELECT_UI_POS.first.y + (SELECT_UI_POS.second.y - SELECT_UI_POS.first.y) / 1.5f, errorNum_, 0xff0000);
#ifdef _DEBUG

		DrawFormatString(mPos.x, mPos.y + 10, 0x00ff00, L"%d:%d", lpMouseController.GetOffsetPos().x,lpMouseController.GetOffsetPos().y );
		DrawFormatString(mPos.x, mPos.y + 30, 0x0000ff, L"%d:%d", mPos.x + static_cast<int>(lpApplication.GetCamera().GetPos().x), mPos.y + static_cast<int>(lpApplication.GetCamera().GetPos().y));
#endif // _DEBUG

	}
	void Delete()
	{

	}
	// 前のシーンへと戻るコールバック用関数
	bool Back()
	{
		scene_->canvas_->ClearUI();
		scene_->nowState_ = CustomState::SELECT_FILE;
		scene_->custom_[scene_->nowState_]->Init(scene_);
		return true;
	}
	// 次のシーンへ移行するコールバック用関数
	bool Next()
	{
		scene_->canvas_->ClearUI();
		scene_->nowState_ = CustomState::ENEMY_CUSTOM;
		scene_->custom_[scene_->nowState_]->Init(scene_);	
		return true;
	}
private:
	MapChipName selChip_;	// 選択中のチップ
	CustomMapScene* scene_;	// シーン保持用関数
	// エラーナンバー
	int errorNum_;
	std::unique_ptr<CustumErrorText>errorText_;
	
};