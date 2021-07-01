#include "TitleScene.h"
#include <DxLib.h>
#include "MainScene.h"
#include "../Application.h"
#include "../Unit/Enemy/Mob/ECircle.h"
#include "../Unit/Player/PlayerMng.h"
#include "../MouseController.h"
#include "../Unit/Enemy/EnemyManager.h"

TitleScene::TitleScene()
{
	image = LoadGraph(L"data/image/Title_logo.png");
	lpApplication.GetCamera().SetScale(1.0f);
	lpApplication.GetCamera().ScaleLock(true);
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
	DrawRotaGraph(420, 150, 1, 0, image, false);

	SetFontSize(40);
	DrawString(280, 400, L"Touch To Start", 0xffffff);
	SetFontSize(16);
}

void TitleScene::DrawUI()
{
	// DrawString(0, 48, L"TitleScene", 0xffffff);
}
