#include "MainScene.h"
#include <DxLib.h>
#include "GameScene.h"
#include "CustomMapScene.h"
#include "../Button/ImageRectButton.h"

MainScene::MainScene()
{
	button_.emplace_back(std::make_unique<ImageRectButton>(VECTOR2(0,100), VECTOR2(150, 80), 
		L"data/image/Custom_Botton1.png", L"data/image/Custom_Botton2.png", [&]() {return false; }, VECTOR2()));
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
