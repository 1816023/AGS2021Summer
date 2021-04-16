#include "TitleScene.h"
#include <DxLib.h>
#include "MainScene.h"
#include "../Unit/Enemy/ECircle.h"
#include "../MouseController.h"

TitleScene::TitleScene()
{
	eCircle_ = new ECircle(Vec2Float(100.0f, 100.0f));
	
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

	return std::move(own);
}

void TitleScene::Draw()
{
	eCircle_->Draw();
	//DrawFormatString( 0, 10, 0xfffff, L"%d, %d", lpMouseController.GetPos().x, lpMouseController.GetPos().y);
	DrawString(0, 0, L"TitleScene", 0xffffff);
}
