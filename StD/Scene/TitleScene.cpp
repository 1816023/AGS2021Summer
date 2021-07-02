#include "TitleScene.h"
#include <DxLib.h>
#include "MainScene.h"
#include "ResultScene.h"
#include "../Application.h"
#include "../Unit/Enemy/Mob/ECircle.h"
#include "../Unit/Player/PlayerMng.h"
#include "../MouseController.h"
#include "../Unit/Enemy/EnemyManager.h"

TitleScene::TitleScene()
{
	logoImage = LoadGraph(L"data/image/Title_logo.png");
	pushImage = LoadGraph(L"data/image/Title_push.png");
	cnt = 255;
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
		return std::make_unique<ResultScene>();
	}
	return std::move(own);
}

void TitleScene::Draw()
{
	DrawRotaGraph(DEF_SCREEN_SIZE_X / 2, 150, 1, 0, logoImage, false);
	if (cnt >= 50)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, cnt);
	}
	else
	{
		cnt = 255;
	}
	DrawRotaGraph(DEF_SCREEN_SIZE_X / 2, 400, 1, 0, pushImage, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	cnt -= 2;
}

void TitleScene::DrawUI()
{
	// DrawString(0, 48, L"TitleScene", 0xffffff);
}
