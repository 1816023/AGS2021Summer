#pragma once
#include "../Scene/CustomMapScene.h"
#include "CustomState.h"
#include "../StringUtil.h"
#define CUSTOM dynamic_cast<Custom*>(scene->map_.get())

struct MapCustom:public CustomStateBase
{
	MapCustom() {};
	~MapCustom() {};
	bool Init(CustomMapScene* scene)
	{
		const int bSize = 64;
		const int bSpace = 20;
		const int basePosX = SELECT_UI_POS.first.x + bSpace;
		const int basePosY = SELECT_UI_POS.first.x + bSize + bSpace;
		auto nFunc = [&](ButtomState& state) {
			if (state.pushFlag = !state.pushFlag)
			{
				scene->selChip_ = static_cast<MapChipName>(std::atoi(_WtS(state.name).c_str()));
			}
			else
			{
				scene->selChip_ = MapChipName::MAX;
			}
		};
		auto sFunc = [&](ButtomState& state) {state.pushFlag = true; CUSTOM->SaveFile(); };

		scene->button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, bSpace * 2), VECTOR2(basePosY, bSize + bSpace * 2), VECTOR2(10, 10), 0x007fff, [&]() {scene->selChip_ = MapChipName::MAINSTAY; return false; }, VECTOR2()));
		scene->buttonText_.emplace_back(ButtonText{ "自拠点",0xffffff,VECTOR2(basePosX,  bSpace * 2 - GetFontSize()) });
		scene->button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace), bSpace * 2), VECTOR2(basePosY + (bSize + bSpace), bSize + bSpace * 2), VECTOR2(10, 10), 0xff0f0f, [&]() {scene->selChip_ = MapChipName::SPAWNER; return false; }, VECTOR2()));
		scene->buttonText_.emplace_back(ButtonText{ "敵出現", 0xffffff, VECTOR2(basePosX + (bSize + bSpace), bSpace * 2 - GetFontSize()) });
		scene->button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace) * 2, bSpace * 2), VECTOR2(basePosY + (bSize + bSpace) * 2, bSize + bSpace * 2), VECTOR2(10, 10), 0xfff00, [&]() {scene->selChip_ = MapChipName::ROOT; return false; }, VECTOR2()));
		scene->buttonText_.emplace_back(ButtonText{ "敵侵攻",0xffffff,VECTOR2(basePosX + (bSize + bSpace) * 2, bSpace * 2 - GetFontSize()) });
		scene->button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX, bSpace + (bSize + bSpace * 2)), VECTOR2(basePosY, bSize + bSpace + (bSize + bSpace * 2)), VECTOR2(10, 10), 0xe3e3e3, [&]() {scene->selChip_ = MapChipName::FIELD; return false; }, VECTOR2()));
		scene->buttonText_.emplace_back(ButtonText{ "自機配置",0xffffff,VECTOR2(basePosX, bSpace + (bSize + bSpace * 2) - GetFontSize()) });
		scene->button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace), bSpace + (bSize + bSpace * 2)), VECTOR2(basePosY + (bSize + bSpace), bSize + bSpace + (bSize + bSpace * 2)), VECTOR2(10, 10), 0x333333, [&]() {scene->selChip_ = MapChipName::WALL; return false; }, VECTOR2()));
		scene->buttonText_.emplace_back(ButtonText{ "設置不可",0xffffff,VECTOR2(basePosX + (bSize + bSpace), bSpace + (bSize + bSpace * 2) - GetFontSize()) });
		scene->button_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(basePosX + (bSize + bSpace) * 2, bSpace + (bSize + bSpace * 2)), VECTOR2(basePosY + (bSize + bSpace) * 2, bSize + bSpace + (bSize + bSpace * 2)), VECTOR2(10, 10), 0xffffff, [&]() {scene->selChip_ = MapChipName::MAX; return false; }, VECTOR2()));
		scene->buttonText_.emplace_back(ButtonText{ "選択解除",0xffffff,VECTOR2(basePosX + (bSize + bSpace) * 2, bSpace + (bSize + bSpace * 2) - GetFontSize()) });
		for (auto&& b : scene->button_)
		{
			b->SetAuto();
		}
		scene->blendAlpha_ = 256;
		scene->selChip_ = MapChipName::MAX;
		scene->LoadText();
		return false;

	}
	void Update(CustomMapScene* scene)
	{
		for (auto&& list : scene->button_)
		{
			list->Update();
		}
		if ((scene->now[KEY_INPUT_BACK]) & (~scene->old[KEY_INPUT_BACK]))
		{
			scene->nowState_ = CustomState::END_CUSTOM;
			scene->custom_[scene->nowState_]->Init(scene);

		}
		VECTOR2 mPos;
		GetMousePoint(&mPos.x, &mPos.y);
		auto cPos = lpApplication.GetCamera().GetPos() * 2.0f;
		if (lpMouseController.GetClicking(MOUSE_INPUT_LEFT))
		{
			if (mPos.x > SELECT_UI_POS.first.x)
			{
			}
			else
			{
				scene->map_->SetChip(VecICast(cPos + mPos), scene->selChip_);
			}
		}

		scene->blendAlpha_ += 2;

	}

	void Draw(CustomMapScene* scene)
	{
		//DrawString(0, 0, L"Custom", 0xffffff);
		// 枠表示
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawRoundRect(SELECT_UI_POS.first.x, SELECT_UI_POS.first.y, SELECT_UI_POS.second.x, SELECT_UI_POS.second.y, 20, 20, 0x555555, true);
		DrawRoundRect(SELECT_UI_POS.first.x, SELECT_UI_POS.first.y, SELECT_UI_POS.second.x, SELECT_UI_POS.second.y, 20, 20, 0xffffff, false);
		DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0x555555, true);
		DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0xffffff, false);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
		// 説明文の表示
		DrawString(TEXT_UI_POS.first.x + 30, TEXT_UI_POS.first.y + (TEXT_UI_POS.second.y - TEXT_UI_POS.first.y) / 5, _StW(scene->textData_[scene->selChip_]).c_str(), 0xffffff);
		VECTOR2 mPos = lpMouseController.GetPos();
		// とりあえずボタンの表示
		/*int shadowOffset = 3;
		int pushuOffset = 1;
		for (auto list : bList_)
		{
			if (list.pushFlag)
			{
				DrawRoundRect(list.luPos.x+ pushuOffset, list.luPos.y+ pushuOffset, list.rdPos.x+ pushuOffset, list.rdPos.y+ pushuOffset, 10, 10, list.CorH, true);

			}
			else
			{
				DrawRoundRect(list.luPos.x + shadowOffset, list.luPos.y + shadowOffset, list.rdPos.x + shadowOffset, list.rdPos.y + shadowOffset, 10, 10, 0x000000, true);
				DrawRoundRect(list.luPos.x, list.luPos.y, list.rdPos.x, list.rdPos.y, 10, 10, list.CorH, true);

			}

		}*/
		for (auto&& list : scene->button_)
		{
			list->Draw();
		}
		for (auto list : scene->buttonText_)
		{
			DrawString(list.pos_.x, list.pos_.y, _StW(list.str_).c_str(), list.color_);
		}
#ifdef _DEBUG

		DrawFormatString(mPos.x, mPos.y + 10, 0x00ff00, L"%d:%d", mPos.x, mPos.y);
		DrawFormatString(mPos.x, mPos.y + 30, 0x0000ff, L"%d:%d", mPos.x + static_cast<int>(lpApplication.GetCamera().GetPos().x), mPos.y + static_cast<int>(lpApplication.GetCamera().GetPos().y));
#endif // _DEBUG



	}
};