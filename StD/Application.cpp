#include "Application.h"
#include "Scene/TitleScene.h"
#include "KeyController.h"
#include "MouseController.h"

bool Application::Init()
{
	ChangeWindowMode(true);
	SetMainWindowText(L"DC&IC");
	int DesktopW, DesktopH;
	GetDefaultState(&DesktopW, &DesktopH, nullptr);
	SetGraphMode(DesktopW, DesktopH, 16);
	//SetWindowSize(854, 480);
	SetGraphMode(854, 480, 16);
	SetWindowSizeChangeEnableFlag(true, true);
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)
	{
		return false;
	}
	sceneController_ = std::make_unique<TitleScene>();
	return true;
}

void Application::Run()
{
	int cnt = 0;
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ProcessMessage() == 0)
	{
		
		ClsDrawScreen();
		sceneController_ = (*sceneController_).Update(std::move(sceneController_));
		Draw();
		lpKeyController.Update();
		lpMouseController.Update();
		ScreenFlip();
	}
}

void Application::Draw()
{
	sceneController_->Draw();
}

void Application::Terminate()
{
	DxLib_End();
}
