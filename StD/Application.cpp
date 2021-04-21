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
		sceneController_ = (*sceneController_).Update(std::move(sceneController_));
		
		lpKeyController.Update();
		lpMouseController.Update();
		auto now = system_clock::now();
		delta = static_cast<float>(duration_cast<microseconds>(now - old).count())* 0.00001f;
		
		old = now;
		
		Draw();
	}
}

void Application::Draw()
{
	ClsDrawScreen();
	// ゲーム描画
	SetDrawScreen(gameScreen_);
	ClsDrawScreen();
	sceneController_->Draw();

	// スクリーンを裏に描画
	SetDrawScreen(DX_SCREEN_BACK);
	static double ud,lr= 0.0;
	static float i= 1.0;
	if (CheckHitKey(KEY_INPUT_UP))
	{
		ud++;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		ud--;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		lr++;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		lr--;
	}
	if (CheckHitKey(KEY_INPUT_W))
	{
		i+= 0.001;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		i-= 0.001;
	}
	DrawRotaGraph2(-lr+ 427, -ud+240, lr+ 427, ud+240, i ,0, gameScreen_, false);
	// ui描画
	sceneController_->DrawUI();
	DrawFormatString(0, 32, 0xffffff, L"%f", delta);
	DrawFormatString(0, 0, 0xffffff, L"pos %f, %f, %f", -lr, ud, i);
	ScreenFlip();
}

float Application::getDelta()
{
	return delta;
}

void Application::Terminate()
{
	DxLib_End();
}
