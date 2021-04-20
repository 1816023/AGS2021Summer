#include "Application.h"
#include "Scene/TitleScene.h"
#include "KeyController.h"
#include "MouseController.h"

using namespace std::chrono;

namespace
{
	int chipSize = 64;
	int mapSize = 30;
}

bool Application::Init()
{
	ChangeWindowMode(true);
	SetMainWindowText(L"DC&IC");
	ExtendWindowInit();

	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	int x, y, col;
	GetScreenState(&x, &y, &col);
	gameScreen_ = MakeScreen(chipSize * mapSize, chipSize * mapSize);
	uiScreen_ = MakeScreen(x, y);
	sceneController_ = std::make_unique<TitleScene>();
	old = system_clock::now();
	return true;
}

void Application::ExtendWindowInit()
{
	int DesktopW, DesktopH;
	GetDefaultState(&DesktopW, &DesktopH, nullptr);
	// 一度ウィンドウを画面のサイズに拡大する
	SetGraphMode(DesktopW, DesktopH, 16);
	// 任意サイズに変更
	SetGraphMode(854, 480, 16);
	SetWindowSizeChangeEnableFlag(true, true);
}

void Application::Run()
{
	int cnt = 0;
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ProcessMessage() == 0)
	{
		ClsDrawScreen();
		sceneController_ = (*sceneController_).Update(std::move(sceneController_));
		
		lpKeyController.Update();
		lpMouseController.Update();
		auto now = system_clock::now();
		delta = static_cast<float>(duration_cast<microseconds>(now - old).count())* 0.00001f;
		DrawFormatString(0, 20, 0xffffff, L"%f", delta);
		old = now;
		// ゲーム描画
		SetDrawScreen(gameScreen_);
		ClsDrawScreen();
		Draw();
		SetDrawScreen(DX_SCREEN_BACK);
		static double i = 1.0;
		i += delta;
		DrawRotaGraph(0, 0, i, 0, gameScreen_, false);
		// ui描画
		SetDrawScreen(gameScreen_);
		ClsDrawScreen();
		Draw();
		SetDrawScreen(DX_SCREEN_BACK);
		DrawGraph(0, i, gameScreen_, false);
		ScreenFlip();	
	
	}
}

void Application::Draw()
{
	sceneController_->Draw();
}

float Application::getDelta()
{
	return delta;
}

void Application::Terminate()
{
	DxLib_End();
}
