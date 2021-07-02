#include "MainScene.h"
#include <DxLib.h>
#include "GameScene.h"
#include "CustomMapScene.h"
#include "../Button/ImageRectButton.h"
#include "../Application.h"
#include "../StringUtil.h"

MainScene::MainScene()
{
	customTransition_ = false;
	gameTransition_ = false;
	drawer_ = &MainScene::GameModeSelectDraw;
	auto bSize = VECTOR2(150, 80);
	auto bPos = VECTOR2(DEF_SCREEN_SIZE_X / 2 - bSize.x / 2, DEF_SCREEN_SIZE_Y / 4);
	std::wstring dir = L"data/image/";

	struct MainButton
	{
		VECTOR2 pos;		// 座標
		std::wstring path;	// ファイル場所
		std::wstring text;	// ボタンのテキスト
		std::function<bool()>func;
		MainButton(std::wstring p, std::wstring s, std::function<bool()>f, VECTOR2 pos) :path(p), text(s), func(f), pos(pos) {};
	};
	// ゲームモード選択画面のボタンリスト
	std::array<MainButton, 2>gmBList = {
		// カスタムへ遷移するボタン
		MainButton(L"Custom_Botton", L"マップカスタム"
		,[&]() {customTransition_ = true; return true; }, bPos),
		// 難易度選択へ移動するボタン
		MainButton(L"Tutorial_Botton", L"ゲーム"
		,[&]() {gameTransition_ = true; return true; }, VECTOR2(bPos.x, bPos.y + bSize.y * 2))
	};
	
	for (auto& gmb : gmBList)
	{
		gameModeButton_.emplace_back(std::make_unique<ImageRectButton>(gmb.pos, bSize,
			dir + gmb.path + L"1.png", dir + gmb.path + L"2.png", gmb.func, VECTOR2()));
		auto wordWidth = GetDrawStringWidth(gmb.text.c_str(), GetStringLength(gmb.text.c_str()));
		gameModeButton_.back()->SetString(_WtS(gmb.text), VECTOR2(bSize.x / 2 - wordWidth / 2, bSize.y / 4));
	}
	//// 難易度選択ボタン
	//bPos = VECTOR2(DEF_SCREEN_SIZE_X / 4 - bSize.x / 2, DEF_SCREEN_SIZE_Y / 4);
	//std::array<MainButton, 2>difBList = {
	//	MainButton(L"Tutorial_Botton", L"チュートリアル"
	//	,[&]() {customTransition_ = true; return true; }, bPos),

	//	MainButton(L"Tutorial_Botton", L"カスタム"
	//	,[&]() {gameTransition_ = true; return true; }, {bPos.x, bPos.y + bSize.y * 2})
	//};
	//std::wstring dir = L"data/image/";
	//for (auto difB : difBList)
	//{
	//	gameModeButton_.emplace_back(std::make_unique<ImageRectButton>(difB.pos, bSize,
	//		dir + difB.path + L"1.png", dir + difB.path + L"2.png", difB.func, VECTOR2()));
	//	auto wordWidth = GetDrawStringWidth(difB.text.c_str(), GetStringLength(difB.text.c_str()));
	//	gameModeButton_.back()->SetString(_WtS(difB.text), VECTOR2(bSize.x / 2 - wordWidth / 2, bSize.y / 4));
	//}

	for (auto& button : gameModeButton_)
	{
		button->SetAuto();
	}
}

MainScene::~MainScene()
{
}

unique_Base MainScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);
	if (gameTransition_)
	{
		return std::make_unique<GameScene>();
	}
	if (customTransition_)
	{
		return std::make_unique<CustomMapScene>();
	}
	if (mapSelectTransition_)
	{
		// マップセレクトへ遷移予定
	}
	for (auto& button : gameModeButton_)
	{
		button->Update();
	}

	return std::move(own);
}

void MainScene::GameModeSelectUpdate()
{
}

void MainScene::DifficuritySelectUpdate()
{
}

void MainScene::GameModeSelectDraw()
{
	VECTOR2 sSize;
	int bit;
	GetScreenState(&sSize.x, &sSize.y, &bit);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 128);
	DrawRoundRect(0, 0, sSize.x, sSize.y, 30, 30, 0xffffff, true);
	DrawRoundRect(0, 0, sSize.x, sSize.y, 30, 30, 0x000000, false);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	for (auto& button : gameModeButton_)
	{
		button->Draw();
	}
}

void MainScene::DifficuritySelectDraw()
{
}

void MainScene::Draw()
{
	
}

void MainScene::DrawUI()
{
	DrawString(100, 100, L"MainScene", 0xffffff);
	(this->*drawer_)();
}
