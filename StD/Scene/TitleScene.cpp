#include "TitleScene.h"
#include <DxLib.h>

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

unique_Base TitleScene::UpData(unique_Base own)
{
	return std::move(own);
}

void TitleScene::Draw()
{
	DrawString(100, 100, L"TitleScene", 0xffffff);
}
