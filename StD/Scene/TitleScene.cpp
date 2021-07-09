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
	logoImage = LoadGraph(L"data/image/Title_logo2.png");
	pushImage = LoadGraph(L"data/image/Title_push.png");
	mobImage[0] = LoadGraph(L"data/image/Hexagon_Pink.png");
	mobImage[1] = LoadGraph(L"data/image/Hexagon_Blue.png");
	mobImage[2] = LoadGraph(L"data/image/Hexagon_Green.png");
	mobImage[3] = LoadGraph(L"data/image/Hexagon_Yellow.png");
	cnt = 255;
	flag = true;
	moveFlag = true;
	pos = { 50,50 };
	speed = { 2,2 };
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

	if (lpMouseController.GetClickUp(MOUSE_INPUT_LEFT))
	{
		return std::make_unique<MainScene>();
	}

	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE]))
	{
		return std::make_unique<MainScene>();
	}
	return std::move(own);
}

void TitleScene::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, mobImage[0], true);

	DrawRotaGraph(DEF_SCREEN_SIZE_X / 2, 150, 1, 0, logoImage, true);
	if (flag)
	{
		cnt -= 2;
		if (cnt >= 100)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, cnt);
		}
		else
		{
			flag = false;
		}
	}
	if (!flag)
	{
		cnt += 2;
		if (cnt <= 255)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, cnt);
		}
		else
		{
			flag = true;
		}
	}
	DrawRotaGraph(DEF_SCREEN_SIZE_X / 2, 370, 1, 0, pushImage, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (DEF_SCREEN_SIZE_X <= pos.x + 32 || 0 >= pos.x - 32)
	{
		speed.x = -1 * speed.x;
	}
	if (DEF_SCREEN_SIZE_Y <= pos.y + 32 || 0 >= pos.y - 32)
	{
		speed.y = -1 * speed.y;
	}

	pos.x += speed.x;
	pos.y += -speed.y;

}

void TitleScene::DrawUI()
{
	// DrawString(0, 48, L"TitleScene", 0xffffff);
}
