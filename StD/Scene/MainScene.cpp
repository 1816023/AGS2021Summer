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
	auto bSize = VECTOR2(150, 80);
	auto bPos = VECTOR2(DEF_SCREEN_SIZE_X / 2 - bSize.x / 2, DEF_SCREEN_SIZE_Y / 4);
	struct MainButton
	{
		std::wstring path;
		std::wstring str;
		std::function<bool()>func;
		MainButton(std::wstring p, std::wstring s, std::function<bool()>f) :path(p), str(s), func(f) {};
	};
	std::array<MainButton, 2>mbList = {
		MainButton(L"Custom_Botton", L"マップカスタム", [&]() {customTransition_ = true; return true; }),
		MainButton(L"Tutorial_Botton", L"ゲーム", [&]() {gameTransition_ = true; return true; })
	};
	std::wstring dir = L"data/image/";
	for (auto mb : mbList)
	{
		button_.emplace_back(std::make_unique<ImageRectButton>(bPos, bSize,
			dir + mb.path + L"1.png", dir + mb.path + L"2.png", mb.func, VECTOR2()));
		auto wordWidth = GetDrawStringWidth(mb.str.c_str(), GetStringLength(mb.str.c_str()));
		button_.back()->SetString(_WtS(mb.str), VECTOR2(bSize.x / 2 - wordWidth / 2, bSize.y / 4));
		bPos.y += bSize.y * 2;
	}

	/*button_.emplace_back(std::make_unique<ImageRectButton>(bPos, bSize,
		L"data/image/Tutorial_Botton1.png", L"data/image/Tutorial_Botton2.png", [&]() {return false; }, VECTOR2()));
	wordWidth = GetDrawStringWidth(L"ゲーム", GetStringLength(L"ゲーム"));
	button_.back()->SetString("ゲーム", VECTOR2(bSize.x / 2 - wordWidth / 2, bSize.y / 4));*/
	for (auto& button : button_)
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
	for (auto& button : button_)
	{
		button->Update();
	}

	return std::move(own);
}

void MainScene::Draw()
{
	
}

void MainScene::DrawUI()
{
	DrawString(100, 100, L"MainScene", 0xffffff);
	for (auto& button : button_)
	{
		button->Draw();
	}
}
