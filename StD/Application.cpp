#include "Application.h"

#include "Scene/TitleScene.h"
#include "KeyController.h"

bool Application::Init()
{
	ChangeWindowMode(true);
	SetMainWindowText(L"DC&IC");
	SetGraphMode(1024, 640, 16);
	if (DxLib_Init() == -1)
	{
		return false;
	}
	sceneController_ = std::make_unique<TitleScene>();
	return true;
}

void Application::Run()
{
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ProcessMessage() == 0)
	{
		ClsDrawScreen();
		sceneController_ = (*sceneController_).UpData(std::move(sceneController_));
		Draw();
		lpKeyController.UpData();
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
