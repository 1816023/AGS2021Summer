#include "MainScene.h"
#include <DxLib.h>
#include "GameScene.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

unique_Base MainScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);

	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE]))
	{
		return std::make_unique<GameScene>();
	}

	return std::move(own);
}

void MainScene::Draw()
{
	DrawString(100, 100, L"MainScene", 0xffffff);
}
