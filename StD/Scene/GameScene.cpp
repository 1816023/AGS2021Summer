#include "GameScene.h"
#include <DxLib.h>
#include "ResultScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);

	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE]))
	{
		return std::make_unique<ResultScene>();
	}

	return std::move(own);
}

void GameScene::Draw()
{
	DrawString(100, 100, L"GameScene", 0xffffff);
}
