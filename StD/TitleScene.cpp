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
