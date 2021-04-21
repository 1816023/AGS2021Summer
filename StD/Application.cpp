#include "Application.h"
#include "Scene/TitleScene.h"
#include "KeyController.h"
#include "MouseController.h"
#include "Camera.h"
#include <cassert>

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
	old_ = system_clock::now();
	camera_ = std::make_unique<Camera>();
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
		camera_->Control();
		lpKeyController.Update();
		lpMouseController.Update();
		auto now = system_clock::now();
		if (GetNoActiveState(true)== 0)
		{
			delta_ = static_cast<float>(duration_cast<microseconds>(now - old_).count()) * 0.00001f;
		}
		old_ = now;
		
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
	auto pos = camera_->GetPos();
	auto scale = camera_->GetScale();
	auto halfScreen = Vec2Int(DEF_SCREEN_SIZE_X / 2, DEF_SCREEN_SIZE_Y / 2);
	DrawRotaGraph2(halfScreen.x -pos.x , halfScreen.y -pos.y, 
				   halfScreen.x + pos.x, halfScreen.y + pos.y, scale, 0,
				   gameScreen_, false);
	// ui描画
	sceneController_->DrawUI();
	DrawFormatString(0, 32, 0xffffff, L"%f", delta_);
	DrawFormatString(0, 16, 0xffffff, L"pos %f, %f,scale %f", pos.x, pos.y, scale);
	ScreenFlip();
}

float Application::GetDelta()
{
	return delta_;
}

Camera& Application::GetCamera()
{
	return *camera_;
}

void Application::Terminate()
{
	DxLib_End();
}
