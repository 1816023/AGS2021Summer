#include "MainScene.h"
#include <DxLib.h>
#include "GameScene.h"
#include "CustomMapScene.h"

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
	if ((now[KEY_INPUT_RETURN]) & (~old[KEY_INPUT_RETURN]))
	{
		return std::make_unique<CustomMapScene>();
	}
	return std::move(own);
}

void MainScene::Draw()
{
	
}

void MainScene::DrawUI()
{
	DrawString(100, 100, L"MainScene", 0xffffff);
}
