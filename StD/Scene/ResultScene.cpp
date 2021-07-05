#include "ResultScene.h"
#include <DxLib.h>
#include "../Application.h"
#include "../MouseController.h"
#include "../Unit/Player/PlayerMng.h"
#include "../Trap/Interference.h"
#include "../VECTOR2.h"
#include "TitleScene.h"

ResultScene::ResultScene()
{
	winImage = LoadGraph(L"data/image/win.png");
	loseImage = LoadGraph(L"data/image/lose.png");
	timeImage = LoadGraph(L"data/image/time.png");
	bestImage = LoadGraph(L"data/image/best.png");
	LoadDivGraph(L"data/image/number.png", 11, 11, 1, 15, 21, number);
	flag = true;
}

ResultScene::~ResultScene()
{
}

unique_Base ResultScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);
	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE]))
	{
		return std::make_unique<TitleScene>();
	}
	return std::move(own);
}

void ResultScene::Draw()
{
	if (flag)
	{
		DrawRotaGraph(DEF_SCREEN_SIZE_X / 2, 100, 1, 0, winImage, false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X / 3, 180, 1, 0, timeImage, false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X / 3, 260, 1, 0, bestImage, false);

		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 0, 180, 1, 0, number[0], false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 1, 180, 1, 0, number[1], false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 2, 180, 1, 0, number[2], false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 3, 180, 1, 0, number[3], false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 4, 180, 1, 0, number[4], false);

		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 0, 260, 1, 0, number[5], false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 1, 260, 1, 0, number[6], false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 2, 260, 1, 0, number[7], false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 3, 260, 1, 0, number[8], false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 4, 260, 1, 0, number[9], false);
		DrawRotaGraph(DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 2 + 20 * 5, 260, 1, 0, number[10], false);
	}
	else
	{
		DrawRotaGraph(DEF_SCREEN_SIZE_X / 2, 100, 1, 0, loseImage, false);
	}
}

void ResultScene::DrawUI()
{
	//DrawString(100, 100, L"ResultScene", 0xffffff);
}
