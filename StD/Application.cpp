#include "Application.h"
#include "Scene/TitleScene.h"
#include "KeyController.h"
#include "MouseController.h"
#include "Camera.h"
#include <cassert>
#include "./Mng/FontMng.h"
#include "./Mng/ImageMng.h"
#include "./Mng/SoundMng.h"
#define MAP_MAX_SIZE 30

using namespace std::chrono;


namespace
{
	int chipSize = 64;
	int mapSize = MAP_MAX_SIZE;
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
	camera_ = std::make_unique<Camera>();
	sceneController_ = std::make_unique<TitleScene>();
	oldTime_ = system_clock::now();

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
		//_dbgStartDraw();
		sceneController_ = (*sceneController_).Update(std::move(sceneController_));
		camera_->Control();
		lpKeyController.Update();
		lpMouseController.Update(camera_->GetPos(), camera_->GetScale());
		
		auto now = system_clock::now();
		if (GetNoActiveState(true)== 0)
		{
			delta_ = static_cast<float>(duration_cast<microseconds>(now - oldTime_).count()) * 0.00001f;
		}
		oldTime_ = now;
		Draw();
	}
	lpFontMng.DeleteHandle();
	lpImageMng.DeleteHandle();
	lpSoundMng.DeleteHandle();
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
	auto pos = VecICast(camera_->GetPos());
	auto scale = camera_->GetScale();
	auto halfScreen = VECTOR2(DEF_SCREEN_SIZE_X / 2, DEF_SCREEN_SIZE_Y / 2);
	DrawRotaGraph2(halfScreen.x , halfScreen.y, 
				   halfScreen.x + pos.x, halfScreen.y + pos.y, scale, 0,
				   gameScreen_, false);
	int x, y;
	GetGraphSize(gameScreen_, &x, &y);
	//DrawRotaGraph(x / 2  - pos.x, y / 2 - pos.y, scale, 0, gameScreen_, false);
	// ui描画
	sceneController_->DrawUI();
	//DrawFormatString(0, 32, 0xffffff, L"%f", delta_);
	//DrawFormatString(0, 16, 0xffffff, L"pos %f, %f,scale %f", -pos.x, pos.y, scale);
	camera_->DebugDraw();
	//_dbgAddDraw();
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

const VECTOR2 Application::GetGameScreenSize()
{
	VECTOR2 vec;
	GetGraphSize(gameScreen_, &vec.x, &vec.y);
	return vec;
}

void Application::Terminate()
{
	DxLib_End();
}
