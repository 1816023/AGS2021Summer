#include "TitleScene.h"
#include <DxLib.h>
#include "MainScene.h"
#include "../Application.h"
#include "../Unit/Enemy/ECircle.h"
#include "../Unit/Player/PlayerMng.h"
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
	pos = { 100,100 };
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

	if (lpMouseController.GetClickTrg(MOUSE_INPUT_LEFT))
	{
		lpPlayerMng.Spawner(PlayerUnit::GREEN, Vec2Float(lpMouseController.GetPos().x, lpMouseController.GetPos().y));
	}
	auto delta = Application::Instance().GetDelta();
	lpPlayerMng.Update(delta,pos);
	return std::move(own);
}

void TitleScene::Draw()
{
	if (!trapFlag)
	{
		if (lpMouseController.GetClickTrg(MOUSE_INPUT_LEFT))
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

	lpPlayerMng.Draw();
}

void TitleScene::DrawUI()
{
	DrawString(0, 0, L"TitleScene", 0xffffff);
}
