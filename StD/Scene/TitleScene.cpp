#include "TitleScene.h"
#include <DxLib.h>
#include "MainScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);

	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE]))
	{
		return std::make_unique<MainScene>();
	}

	return std::move(own);
}

void TitleScene::Draw()
{
	DrawString(100, 100, L"TitleScene", 0xffffff);
}
