#include "TitleScene.h"
#include <DxLib.h>
#include "MainScene.h"
#include "../Mng/SoundMng.h"
#include "../Application.h"
#include "../MouseController.h"

TitleScene::TitleScene()
{
	logoImage = LoadGraph(L"data/image/Title_logo2.png");
	pushImage = LoadGraph(L"data/image/Title_push.png");
	mobImage = LoadGraph(L"data/image/Hexagon_Pink.png");
	cnt = 255;
	flag = true;
	pos = { 50,50 };
	speed = { 2,2 };
	lpSoundMng.StartSound("data/Sound/SE/BGM2.mp3", PlayType::LOOP);
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
		lpSoundMng.StopSound("data/Sound/SE/BGM2.mp3");
		return std::make_unique<MainScene>();
	}

	return std::move(own);
}

void TitleScene::Draw()
{
	// mobˆÚ“®(”pŽ~—\’è
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
	DrawRotaGraph(pos.x, pos.y, 1, 0, mobImage, true);
	DrawRotaGraph(DEF_SCREEN_SIZE_X / 2, 150, 1, 0, logoImage, true);
	// PUSHƒƒS“_–Å
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, cnt);
	if (flag)
	{
		cnt -= 2;
		if (cnt > 100)
		{
			DrawRotaGraph(DEF_SCREEN_SIZE_X / 2, 370, 1, 0, pushImage, true);
		}
		else
		{
			flag = false;
		}
	}
	if (!flag)
	{
		cnt += 2;
		if (cnt < 255)
		{
			DrawRotaGraph(DEF_SCREEN_SIZE_X / 2, 370, 1, 0, pushImage, true);
		}
		else
		{
			flag = true;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
