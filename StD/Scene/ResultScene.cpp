#include "ResultScene.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

unique_Base ResultScene::UpData(unique_Base own)
{
	return std::move(own);
}
