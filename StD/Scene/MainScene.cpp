#include "MainScene.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

unique_Base MainScene::UpData(unique_Base own)
{
	return std::move(own);
}
