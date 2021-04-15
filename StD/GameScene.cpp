#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

unique_Base GameScene::UpData(unique_Base own)
{
	return std::move(own);
}
