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
#include "../Trap/TrapManager.h"
#include "../Unit/Enemy/EnemyManager.h"

TitleScene::TitleScene()
{
	trapFlag = false;
	cnt = 0;
	HP = 50;
	pos = { 100,100 };
	speed = 2;
	player_ = std::make_unique<PlayerMng>();
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

	if (lpMouseController.GetClickTrg(MOUSE_INPUT_LEFT))
	{
		player_->Spawner(PlayerUnit::BLUE, Vec2Float(lpMouseController.GetPos().x, lpMouseController.GetPos().y));
	}
	auto delta = Application::Instance().GetDelta();
	player_->Update(delta,pos);
	return std::move(own);
}

void TitleScene::Draw()
{
	if (!trapFlag && lpMouseController.GetClickTrg(MOUSE_INPUT_LEFT))
	{
		lpTrapManager.Spawner(TRAP_ID::INTERFERENCE, Vec2Float(lpMouseController.GetPos().x, lpMouseController.GetPos().y));
		trapFlag = true;
	}
	if (trapFlag)
	{
		cnt++;
		lpTrapManager.Draw();
		if (cnt > 300)
		{
			cnt = 0;
			trapFlag = false;
			lpTrapManager.Delete();
		}
	}
	auto delaySpeed = speed * player_->SpeedDelay();
	pos.x += (delaySpeed>=0 ? delaySpeed:0);
	DrawBox(pos.x, pos.y, pos.x + 60, pos.y + 60, 0xffffff, true);

	DrawFormatString( pos.x+70, pos.y, 0xfffff, L"HP:%d",HP);
	//DrawFormatString(50, 50, 0xffffff, L"HP : %d", HP);

	player_->Draw();
}

void TitleScene::DrawUI()
{
	DrawString(0, 48, L"TitleScene", 0xffffff);
}
