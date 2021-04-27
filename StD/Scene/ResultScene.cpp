#include "ResultScene.h"
#include <DxLib.h>
#include "../Application.h"
#include "../MouseController.h"
#include "../Unit/Player/PlayerMng.h"
#include "../VECTOR2.h"
#include "MainScene.h"

ResultScene::ResultScene()
{
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
		return std::make_unique<MainScene>();
	}

	if (lpMouseController.GetClickTrg())
	{
		lpPlayerMng.Spawner(PlayerUnit::YELLOW,Vec2Float(lpMouseController.GetPos().x, lpMouseController.GetPos().y));
	}
	auto delta = Application::Instance().GetDelta();
	lpPlayerMng.Update(delta);
	return std::move(own);
}

void ResultScene::Draw()
{
	lpPlayerMng.Draw();
}

void ResultScene::DrawUI()
{
	DrawString(100, 100, L"ResultScene", 0xffffff);
}
