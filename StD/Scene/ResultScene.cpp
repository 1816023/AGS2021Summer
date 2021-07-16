#include "ResultScene.h"
#include <DxLib.h>
#include "../Application.h"
#include "../MouseController.h"
#include "../Unit/Player/PlayerMng.h"
#include "../Trap/Interference.h"
#include "../VECTOR2.h"
#include "TitleScene.h"

ResultScene::ResultScene(bool flag)
{
	winImage = LoadGraph(L"data/image/win.png");
	loseImage = LoadGraph(L"data/image/lose.png");
	timeImage = LoadGraph(L"data/image/time.png");
	bestImage = LoadGraph(L"data/image/best.png");
	LoadDivGraph(L"data/image/number.png", 11, 11, 1, 15, 21, number);
	resultFlag = flag;
	time = 0;
	second = 0;
	minute = 0;
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
		return std::make_unique<TitleScene>();
	}

	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE]))
	{
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
		DrawRotaGraph(DEF_SCREEN_SIZE_X / 2, 100, 1, 0, winImage, false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X / 3, 180, 1, 0, timeImage, false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X / 3, 260, 1, 0, bestImage, false);

		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 0, 180, 1, 0, number[minute / 10], false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 1, 180, 1, 0, number[minute % 10], false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 2, 180, 1, 0, number[10], false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 3, 180, 1, 0, number[second / 10], false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 4, 180, 1, 0, number[second % 10], false);
	}
	else
	{
		DrawRotaGraph(DEF_SCREEN_SIZE_X / 2, 100, 1, 0, loseImage, false);
	}

	DrawFormatString(0, 200, 0xffffff, L"minute %d, second %d, time %d", minute, second, time);
}
