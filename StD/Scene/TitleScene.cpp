#include "TitleScene.h"
#include <DxLib.h>
#include "MainScene.h"
#include "../Unit/Enemy/ECircle.h"
#include "../MouseController.h"
#include "../Trap/SlipDamage.h"
#include "../Trap/Support.h"
#include "../Trap/Explosion.h"
#include "../Trap/Interference.h"
#include "../Unit/Enemy/EnemyManager.h"

TitleScene::TitleScene()
{

	slipDamage = new SlipDamage(lpMouseController.GetPos());
	support = new Support(lpMouseController.GetPos());
	explosion = new Explosion(lpMouseController.GetPos());
	interference = new Interference(lpMouseController.GetPos());

	trapFlag = false;
	cnt = 0;
	HP = 50;
	pos = { 10,100 };
	speed = 2;
}

TitleScene::~TitleScene()
{
	delete slipDamage;
	delete support;
	delete explosion;
	delete interference;
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
	if (!trapFlag)
	{
		if (lpMouseController.GetClickTrg())
		{
			interference = new Interference(lpMouseController.GetPos());
			trapFlag = true;
		}
	}
	if (trapFlag)
	{
		cnt++;
		interference->Draw();
		if (cnt > 300)
		{
			cnt = 0;
			trapFlag = false;
		}
	}
	pos.x += interference->Delay(speed, trapFlag);
	DrawBox(pos.x, pos.y, pos.x+60, pos.y+60, 0xffffff, true);

	//DrawFormatString( 0, 10, 0xfffff, L"%d, %d", lpMouseController.GetPos().x, lpMouseController.GetPos().y);
	//DrawFormatString(50, 50, 0xffffff, L"HP : %d", HP);
	
}

void TitleScene::DrawUI()
{
	DrawString(0, 0, L"TitleScene", 0xffffff);
}
