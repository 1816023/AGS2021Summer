#include "Application.h"

bool Application::Init()
{
	ChangeWindowMode(true);
	SetMainWindowText(L"DC&IC");
	SetGraphMode(1024, 640, 16);
	if (DxLib_Init() == -1)
	{
		return false;
	}
}

void Application::Update()
{
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ProcessMessage() == 0)
	{
		ClsDrawScreen();
		Draw();
		ScreenFlip();
	}
}

void Application::Draw()
{
}

void Application::Terminate()
{
	DxLib_End();
}
