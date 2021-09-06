#include "ResultScene.h"
#include <DxLib.h>
#include "../Application.h"
#include "../MouseController.h"
#include "../Mng/SoundMng.h"
#include "../Unit/Player/PlayerMng.h"
#include "../VECTOR2.h"
#include "../NumberUI.h"
#include "TitleScene.h"


ResultScene::ResultScene(bool flag)
{
	winImage = LoadGraph(L"data/image/win.png");
	loseImage = LoadGraph(L"data/image/lose.png");
	pushImage = LoadGraph(L"data/image/Result.png");
	resultFlag = flag;
	time = 0;
	second = 0;
	minute = 0;
	cnt = 255;
	flag = true;
	lpSoundMng.StartSound("data/Sound/SE/BGM4.mp3", PlayType::LOOP);
}

ResultScene::~ResultScene()
{
}

unique_Base ResultScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);

	if (lpMouseController.GetClickUp(MOUSE_INPUT_LEFT))
	{
		lpSoundMng.StopSoundAll();
		//lpSoundMng.StopSound("data/Sound/SE/BGM4.mp3");
		return std::make_unique<TitleScene>();
	}

	return std::move(own);
}

void ResultScene::Draw()
{
	time+=5;
	second = time / 60;
	if (second > 59)
	{
		time = 0;
		second = 0;
		minute++;
	}
}

void ResultScene::DrawUI()
{
	if (resultFlag)
	{
		DrawRotaGraph(DEF_SCREEN_SIZE_X / 2, 150, 1, 0, winImage, true);
	}
	else
	{
		DrawRotaGraph(DEF_SCREEN_SIZE_X / 2, 150, 1, 0, loseImage, true);
	}
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
