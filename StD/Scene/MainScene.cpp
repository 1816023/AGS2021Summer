#include "MainScene.h"
#include <DxLib.h>
#include "GameScene.h"
#include "CustomMapScene.h"
#include "../GUI/Button/ImageRectButton.h"
#include "../Application.h"
#include "../StringUtil.h"
#include "../GUI/Canvas.h"

MainScene::MainScene()
{
	customTransition_ = false;
	gameTransition_ = false;
	updater_ = &MainScene::GameModeSelectUpdate;
	drawer_ = &MainScene::GameModeSelectDraw;

	canvas_ = std::make_unique<Canvas>(VECTOR2(0, 0), VECTOR2(856, 480));
	auto bSize = VECTOR2(150, 80);
	auto bPos = VECTOR2(DEF_SCREEN_SIZE_X / 2 - bSize.x / 2, DEF_SCREEN_SIZE_Y / 4);
	std::wstring dir = L"data/image/";

	UI* b = new ImageRectButton(bSize,
		dir + L"Custom_Botton1.png", dir + L"Custom_Botton2.png", [&]() {customTransition_ = true; return true; }, VECTOR2());
	canvas_->AddUIByID(b, Justified::RIGHT_UP);

	struct MainButton
	{
		VECTOR2 pos;		// 座標
		std::wstring path;	// ファイル場所
		std::wstring text;	// ボタンのテキスト
		std::function<bool()>func;
		MainButton(std::wstring p, std::wstring s, std::function<bool()>f, VECTOR2 pos) :path(p), text(s), func(f), pos(pos) {};
	};
	// ゲームモード選択画面のボタンリスト
	std::vector<MainButton>gmBList; 
		// カスタムへ遷移するボタン
	gmBList.emplace_back(MainButton(L"Custom_Botton", L"マップカスタム"
		, [&]() {customTransition_ = true; return true; }, bPos));
		// 難易度選択へ移動するボタン
	gmBList.emplace_back(MainButton(L"Tutorial_Botton", L"ゲーム"
		, [&]() {
			updater_ = &MainScene::DifficuritySelectUpdate;
			drawer_ = &MainScene::DifficuritySelectDraw;
			return true;
		}, VECTOR2(bPos.x, bPos.y + bSize.y * 2)));
	
	auto createButton = [&](std::list<std::unique_ptr<Button>>& button, std::vector<MainButton>& mbList)
 	{
		for (auto& gmb : mbList)
		{
			button.emplace_back(std::make_unique<ImageRectButton>(gmb.pos, bSize,
				dir + gmb.path + L"1.png", dir + gmb.path + L"2.png", gmb.func, VECTOR2()));
			auto wordWidth = GetDrawStringWidth(gmb.text.c_str(), GetStringLength(gmb.text.c_str()));
			button.back()->SetString(_WtS(gmb.text), VECTOR2(bSize.x / 2 - wordWidth / 2, bSize.y / 4));
		}
		for (auto& b : button)
		{
			b->SetReversePush();
			b->SetAuto();
		}
	};

	createButton(gameModeButton_, gmBList);
	// 難易度選択ボタン
	bPos = VECTOR2(DEF_SCREEN_SIZE_X / 4 - bSize.x / 2, DEF_SCREEN_SIZE_Y / 4);
	std::vector<MainButton>difBList;
	difBList.emplace_back(MainButton(L"Tutorial_Botton", L"TUTORIAL"
		, [&]() {gameTransition_ = true; return true; }, bPos));

	difBList.emplace_back(MainButton(L"Custom_Botton", L"CUSTOM"
		, [&]() {gameTransition_ = true; return true; }, { bPos.x, bPos.y + bSize.y * 2 }));

	bPos.x += DEF_SCREEN_SIZE_X / 4;
	difBList.emplace_back(MainButton(L"Easy_Button", L"EASY"
		, [&]() {gameTransition_ = true; return true; }, { bPos.x, bPos.y   }));

	difBList.emplace_back(MainButton(L"Normal_Botton", L"NORMAL"
		, [&]() {gameTransition_ = true; return true; }, { bPos.x, bPos.y + bSize.y }));

	difBList.emplace_back(MainButton(L"Hard_Botton", L"HARD"
		, [&]() {gameTransition_ = true; return true; }, { bPos.x, bPos.y + bSize.y * 2 }));
	bPos.x += DEF_SCREEN_SIZE_X / 4;
	createButton(difSelectButton_, difBList);

	// 戻るボタン
	bSize = { 100, 67 };
	backButton_ = std::make_unique<ImageRectButton>(VECTOR2( bPos.x, bPos.y), bSize,
		dir + L"Back_Button1.png", dir + L"Back_Button2.png", 
		[&](){	
			updater_ = &MainScene::GameModeSelectUpdate;
			drawer_ = &MainScene::GameModeSelectDraw; return true;
		});
	auto wordWidth = GetDrawStringWidth(L"BACK", GetStringLength(L"BACK"));
	backButton_->SetString(_WtS(L"BACK"), VECTOR2(bSize.x / 2 - wordWidth / 2, bSize.y / 2 - GetFontSize()/2));
	backButton_->SetAuto();


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
	canvas_->Update();
	(this->*updater_)();
	return std::move(own);
}

void MainScene::GameModeSelectUpdate()
{
	for (auto& button : gameModeButton_)
	{
		button->Update();
	}
}

void MainScene::DifficuritySelectUpdate()
{
	for (auto& button : difSelectButton_)
	{
		button->Update();
	}
	backButton_->Update();
}

void MainScene::GameModeSelectDraw()
{
	for (auto& button : gameModeButton_)
	{
		button->Draw();
	}
}

void MainScene::DifficuritySelectDraw()
{
	for (auto& button : difSelectButton_)
	{
		button->Draw();
	}
	backButton_->Draw();
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
	DrawRoundRect(0, 0, sSize.x, sSize.y, 30, 30, 0xffffff, true);
	DrawRoundRect(0, 0, sSize.x, sSize.y, 30, 30, 0x000000, false);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	canvas_->Draw();
	(this->*drawer_)();
}
