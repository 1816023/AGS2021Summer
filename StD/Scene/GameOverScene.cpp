#include "GameOverScene.h"
#include <DxLib.h>
#include "../Application.h"
#include "../MouseController.h"
#include "../VECTOR2.h"
#include "TitleScene.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

unique_Base GameOverScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);
	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE]))
	{
		return std::make_unique<TitleScene>();
	}
	return std::move(own);
}

void GameOverScene::Draw()
{
}

void GameOverScene::DrawUI()
{
	DrawString(100, 100, L"GameOverScene", 0xffffff);
}
