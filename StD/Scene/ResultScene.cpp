#include "ResultScene.h"
#include <DxLib.h>
#include "../Application.h"
#include "../MouseController.h"
#include "../Unit/Player/PlayerMng.h"
#include "../Trap/Interference.h"
#include "../VECTOR2.h"
#include "MainScene.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

unique_Base ResultScene::Update(unique_Base own)
{
	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE]))
	{
		return std::make_unique<MainScene>();
	}
	return std::move(own);
}

void ResultScene::Draw()
{
	lpPlayerMng.Draw();
}

void ResultScene::DrawUI()
{
	DrawString(100, 100, L"ResultScene", 0xffffff);
}
