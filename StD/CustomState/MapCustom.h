#pragma once
#include "../Scene/CustomMapScene.h"
#include "CustomState.h"
#include "../StringUtil.h"
#include "../Map/Astar.h"
#include "../MapEnum.h"
#include "../GUI/CustumErrorText.h"
#include "../GUI/Canvas.h"
#include "../GUI/UIText.h"

struct MapCustom : public CustomStateBase
{

	MapCustom() {};
	~MapCustom() {}
	bool Init(CustomMapScene* scene)override
	{
		scene_ = scene;
		scene->canvas_->SetActive(true);
		scene->textCanvas_->SetActive(true);

		// 説明文
		UIText* explanation;
		explanation = new UIText({ 3,(TEXT_UI_POS.second.y - TEXT_UI_POS.first.y) / 5 }, L"TestText");

		// ボタンとテキスト一部の作成
		const int bSize = 64;
		const int bSpace = 20;
		std::list<Button*>button;
		std::list<UIText*>mainText;
		VECTOR2 roundS = { 10, 10 };
		button.emplace_back(new RoundRectButton(VECTOR2(bSpace, bSpace * 2), VECTOR2(bSize, bSize), roundS, 0x007fff, [&]() {selChip_ = MapChipName::MAINSTAY; return true; }));
		mainText.emplace_back(new UIText(VECTOR2(bSpace, bSpace * 2 - GetFontSize()), L"自拠点"));
		button.emplace_back(new RoundRectButton(VECTOR2(bSize + bSpace * 2, bSpace * 2), VECTOR2(bSize, bSize), roundS, 0xff0f0f, [&]() {selChip_ = MapChipName::SPAWNER; return true; }));
		mainText.emplace_back(new UIText(VECTOR2(bSize + bSpace * 2, bSpace * 2 - GetFontSize()), L"敵出現"));
		button.emplace_back(new RoundRectButton(VECTOR2(bSize * 2 + bSpace * 3, bSpace * 2), VECTOR2(bSize, bSize), roundS, 0xfff00, [&]() {selChip_ = MapChipName::ROOT; return true; }));
		mainText.emplace_back(new UIText(VECTOR2(bSize * 2 + bSpace * 3, bSpace * 2 - GetFontSize()), L"敵侵攻"));
		button.emplace_back(new RoundRectButton(VECTOR2(bSpace, bSize + bSpace * 3), VECTOR2(bSize, bSize), roundS, 0xe3e3e3, [&]() {selChip_ = MapChipName::FIELD; return true; }));
		mainText.emplace_back(new UIText(VECTOR2(bSpace, bSize + bSpace * 3 - GetFontSize()), L"自機配置"));
		button.emplace_back(new RoundRectButton(VECTOR2(bSize + bSpace * 2, bSize + bSpace * 3), VECTOR2(bSize, bSize), roundS, 0x333333, [&]() {selChip_ = MapChipName::WALL; return true; }));
		mainText.emplace_back(new UIText(VECTOR2(bSize + bSpace * 2, bSize + bSpace * 3 - GetFontSize()), L"設置不可"));
		button.emplace_back(new RoundRectButton(VECTOR2(bSize * 2 + bSpace * 3, bSize + bSpace * 3), VECTOR2(bSize, bSize), roundS, 0xffffff, [&]() {selChip_ = MapChipName::MAX; return true; }));
		mainText.emplace_back(new UIText(VECTOR2(bSize * 2 + bSpace * 3, bSize + bSpace * 3 - GetFontSize()), L"選択解除"));

		// システム系のボタン
		button.emplace_back(new RoundRectButton(VECTOR2(bSpace, SELECT_UI_POS.second.y - bSize / 2 - bSpace), VECTOR2(bSize, bSize / 2), roundS, 0xffffff, std::bind(&MapCustom::Back, this)));
		button.back()->SetString("Back", VECTOR2(bSize / 2 - GetDrawStringWidth(L"Back", GetStringLength(L"Back")) / 2, bSize / 4 - GetFontSize() / 2));
		button.emplace_back(new RoundRectButton(VECTOR2(bSpace * 2 + bSize, SELECT_UI_POS.second.y - bSize / 2 - bSpace), VECTOR2(bSize, bSize / 2), roundS, 0xffffff, std::bind(&MapCustom::Next, this)));
		button.back()->SetString("Next", VECTOR2(bSize / 2 - GetDrawStringWidth(L"Next", GetStringLength(L"Next")) / 2, bSize / 4 - GetFontSize() / 2));
		button.emplace_back(new RoundRectButton(VECTOR2(bSpace * 3 + bSize * 2, SELECT_UI_POS.second.y - bSize / 2 - bSpace), VECTOR2(bSize, bSize / 2), roundS, 0xffffff, [&, scene]() {
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
			}));
		button.back()->SetString("Save", VECTOR2(bSize / 2 - GetDrawStringWidth(L"Save", GetStringLength(L"Save")) / 2, bSize / 4 - GetFontSize() / 2));

		// エラーテキスト
		auto errorT = new UIText({ 10, static_cast<int>((SELECT_UI_POS.second.y - SELECT_UI_POS.first.y) / 1.5f)}, L"Error", 0xff0000);
		errorText_ = std::make_unique<CustumErrorText>();
		errorNum_ = 0;
		// エラーの内容
		errorText_->AddErrorText("");
		errorText_->AddErrorText("拠点とスポナーの数が多すぎます。\n最大数は各2つまでです。");
		errorText_->AddErrorText("拠点の数が多すぎます。\n最大数は2つまでです。");
		errorText_->AddErrorText("スポナーの数が多すぎます。\n最大数は2つまでです。");
		errorText_->AddErrorText("拠点とスポナーを設置してください。");
		errorText_->AddErrorText("拠点を設置してください。");
		errorText_->AddErrorText("スポナーを設置してください。");

		// 全てのボタンを自動化する
		int cnt = 0;
		for (auto& b : button)
		{
			b->SetAuto();
			scene->canvas_->AddUIByID(b, cnt++);
		}
		// キャンバスにテキストをセット
		for (auto& t : mainText)
		{
			scene->canvas_->AddUIByID(t, cnt++);
		}
		scene->textCanvas_->AddUIByName(explanation, L"説明文");
		scene->canvas_->AddUIByName(errorT, L"エラー");
		scene->blendAlpha_ = 256;
		selChip_ = MapChipName::MAX;
		scene->LoadText("map");
		
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
		dynamic_cast<UIText*>(scene->textCanvas_->GetUIByName(L"説明文"))->SetText(_StW(scene->textData_[selChip_]));
		dynamic_cast<UIText*>(scene->canvas_->GetUIByName(L"エラー"))->SetText(errorText_->GetErrorText()[errorNum_]);
	}

	void Draw(CustomMapScene* scene)override
	{
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
		scene_->textCanvas_->ClearUI();
		scene_->nowState_ = CustomState::SELECT_FILE;
		scene_->custom_[scene_->nowState_]->Init(scene_);
		return true;
	}

	// 次のシーンへ移行するコールバック用関数
	bool Next()
	{
		if (scene_->cusMap_->GetSpawner().size() == 0 && scene_->cusMap_->GetMainStay().size() == 0)
		{
			errorNum_ = static_cast<int>(ErrorCode::NonMsSpError);
			return false;
		}

		if (scene_->cusMap_->GetSpawner().size() == 0)
		{
			errorNum_ = static_cast<int>(ErrorCode::NonSpError);
			return false;
		}

		if (scene_->cusMap_->GetMainStay().size() == 0)
		{
			errorNum_ = static_cast<int>(ErrorCode::NonMsError);
			return false;
		}
		
		scene_->canvas_->ClearUI();
		scene_->textCanvas_->ClearUI();
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