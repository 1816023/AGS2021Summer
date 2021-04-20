#include "TitleScene.h"
#include <DxLib.h>
#include "MainScene.h"
#include "../Unit/Enemy/ECircle.h"
#include "../MouseController.h"
#include "../SlipDamage.h"

TitleScene::TitleScene()
{

slipDamage = new SlipDamage(lpMouseController.GetPos());

	trapFlag = false;
	cnt = 0;}

TitleScene::~TitleScene()
{
	delete slipDamage;
}

unique_Base TitleScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);

	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE]))
	{
		return std::make_unique<MainScene>();
	}

	slipDamage->Update();

	return std::move(own);
}

void TitleScene::Draw()
{
	if (!trapFlag)
	{
		if (lpMouseController.GetClickTrg())
		{
			slipDamage = new SlipDamage(lpMouseController.GetPos());
			trapFlag = true;
		}
	}
	if (trapFlag)
	{
		cnt++;
		slipDamage->Draw();
		if (cnt > 300)
		{
			cnt = 0;
			trapFlag = false;
		}
	}
	//DrawFormatString( 0, 10, 0xfffff, L"%d, %d", lpMouseController.GetPos().x, lpMouseController.GetPos().y);
	
}

void TitleScene::DrawUI()
{
	DrawString(0, 0, L"TitleScene", 0xffffff);
}
