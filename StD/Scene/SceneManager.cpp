#include "SceneManager.h"
#include <DxLib.h>
#include "TitleScene.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

bool SceneManager::Run()
{
	if (!SysInit())
	{
		return false;
	}
	sceneController = std::make_unique<TitleScene>();
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ProcessMessage() == 0)
	{
		sceneController = (*sceneController).UpData(std::move(sceneController));
	}

	return true;
}

bool SceneManager::SysInit(void)
{
	ChangeWindowMode(true);
	SetMainWindowText(L"DC&IC");
	SetGraphMode(1024, 640, 16);
	if (DxLib_Init() == -1)
	{
		return false;
	}

	return true;
}
