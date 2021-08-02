#include "MainScene.h"
#include <DxLib.h>
#include "GameMapSellectScene.h"
#include "GameScene.h"
#include "CustomMapScene.h"
#include "../GUI/Button/ImageRectButton.h"
#include "../Application.h"
#include "../StringUtil.h"
#include "../GUI/Canvas.h"

MainScene::MainScene()
{
	Init();

}

MainScene::MainScene(bool flag)
{
	Init();
	updater_ = &MainScene::DifficuritySelectUpdate;
	drawer_ = &MainScene::DifficuritySelectDraw;
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
		return std::make_unique<GameMapSellectScene>();
	}
	if (customTransition_)
	{
		return std::make_unique<CustomMapScene>();
	}
	if (mapSelectTransition_)
	{
		// マップセレクトへ遷移予定
	}
	(this->*updater_)();
	return std::move(own);
}

void MainScene::Init()
{
	customTransition_ = false;
	gameTransition_ = false;
	updater_ = &MainScene::GameModeSelectUpdate;
	drawer_ = &MainScene::GameModeSelectDraw;

	gameModeCanvas_ = std::make_unique<Canvas>(VECTOR2(0, 0), VECTOR2(DEF_SCREEN_SIZE_X, DEF_SCREEN_SIZE_Y));
	gameModeCanvas_->SetColor(0xff0055);
	difSelectCanvas_ = std::make_unique<Canvas>(VECTOR2(0, 0), VECTOR2(DEF_SCREEN_SIZE_X, DEF_SCREEN_SIZE_Y));
	difSelectCanvas_->SetColor(0xffff00);
	auto bSize = VECTOR2(150, 80);
	auto bPos = VECTOR2(DEF_SCREEN_SIZE_X / 2 - bSize.x / 2, DEF_SCREEN_SIZE_Y / 4);
	std::wstring dir = L"data/image/";

	struct MainButton
	{
		VECTOR2 pos;		// 座標
		std::wstring path;	// ファイル場所
		std::wstring text;	// ボタンのテキスト
		std::function<bool()>func;
		int id;
		MainButton(std::wstring p, std::wstring s, std::function<bool()>f, VECTOR2 pos, int i) :path(p), text(s), func(f), pos(pos), id(i) {};
	};
	// ゲームモード選択画面のボタンリスト
	std::vector<MainButton>gmBList;
	// カスタムへ遷移するボタン
	gmBList.emplace_back(MainButton(L"Custom_Botton", L"マップカスタム"
		, [&]() {customTransition_ = true; return true; }, bPos, 0));
	// 難易度選択へ移動するボタン
	gmBList.emplace_back(MainButton(L"Tutorial_Botton", L"ゲーム"
		, [&]() {
			updater_ = &MainScene::DifficuritySelectUpdate;
			drawer_ = &MainScene::DifficuritySelectDraw;
			return true;
		}, VECTOR2(bPos.x, bPos.y + bSize.y * 2), 1));

	auto createButton = [&](std::unique_ptr<Canvas>& canvas, std::vector<MainButton>& mbList)
	{
		for (auto& gmb : mbList)
		{
			auto b = new ImageRectButton(gmb.pos, bSize,
				dir + gmb.path + L"1.png", dir + gmb.path + L"2.png", gmb.func);
			auto wordWidth = GetDrawStringWidth(gmb.text.c_str(), GetStringLength(gmb.text.c_str()));
			b->SetString(_WtS(gmb.text), VECTOR2(bSize.x / 2 - wordWidth / 2, bSize.y / 4));
			b->SetReversePush();
			b->SetAuto();
			canvas->AddUIByID(b, gmb.id);
		}
	};

	createButton(gameModeCanvas_, gmBList);
	// 難易度選択ボタン
	int id = 0;
	bPos = VECTOR2(DEF_SCREEN_SIZE_X / 4 - bSize.x / 2, DEF_SCREEN_SIZE_Y / 4);
	std::vector<MainButton>difBList;
	difBList.emplace_back(MainButton(L"Tutorial_Botton", L"TUTORIAL"
		, [&]() {gameTransition_ = true; return true; }, bPos, id));

	difBList.emplace_back(MainButton(L"Custom_Botton", L"CUSTOM"
		, [&]() {gameTransition_ = true; return true; }, { bPos.x, bPos.y + bSize.y * 2 }, ++id));

	bPos.x += DEF_SCREEN_SIZE_X / 4;
	difBList.emplace_back(MainButton(L"Easy_Button", L"EASY"
		, [&]() {gameTransition_ = true; return true; }, { bPos.x, bPos.y }, ++id));

	difBList.emplace_back(MainButton(L"Normal_Botton", L"NORMAL"
		, [&]() {gameTransition_ = true; return true; }, { bPos.x, bPos.y + bSize.y }, ++id));

	difBList.emplace_back(MainButton(L"Hard_Botton", L"HARD"
		, [&]() {gameTransition_ = true; return true; }, { bPos.x, bPos.y + bSize.y * 2 }, ++id));
	bPos.x += DEF_SCREEN_SIZE_X / 4;
	createButton(difSelectCanvas_, difBList);

	// 戻るボタン
	bSize = { 100, 67 };
	auto backButton = new ImageRectButton(bPos, bSize,
		dir + L"Back_Button1.png", dir + L"Back_Button1.png",
		[&]() {
			updater_ = &MainScene::GameModeSelectUpdate;
			drawer_ = &MainScene::GameModeSelectDraw; return true;
		});
	auto wordWidth = GetDrawStringWidth(L"BACK", GetStringLength(L"BACK"));
	backButton->SetString(_WtS(L"BACK"), VECTOR2(bSize.x / 2 - wordWidth / 2, bSize.y / 2 - GetFontSize() / 2));
	backButton->SetAuto();
	difSelectCanvas_->AddUIByID(backButton, ++id);

}

void MainScene::GameModeSelectUpdate()
{
	gameModeCanvas_->Update();
}

void MainScene::DifficuritySelectUpdate()
{
	difSelectCanvas_->Update();
}

void MainScene::GameModeSelectDraw()
{
	gameModeCanvas_->Draw();
}

void MainScene::DifficuritySelectDraw()
{
	difSelectCanvas_->Draw();
}

void MainScene::Draw()
{

}

void MainScene::DrawUI()
{
	DrawString(100, 100, L"MainScene", 0xffffff);
	VECTOR2 sSize;
	int bit;
	GetScreenState(&sSize.x, &sSize.y, &bit);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 64);
	DrawRoundRect(10, 10, sSize.x-10, sSize.y-10, 30, 30, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	DrawRoundRect(10, 10, sSize.x-10, sSize.y-10, 30, 30, 0xffffff, false);

	(this->*drawer_)();
}
