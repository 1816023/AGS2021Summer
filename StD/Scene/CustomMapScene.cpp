#include <DxLib.h>
#include "TitleScene.h"
#include "CustomMapScene.h"

CustomMapScene::CustomMapScene()
{
}

CustomMapScene::~CustomMapScene()
{
}

unique_Base CustomMapScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);

	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE]))
	{
		return std::make_unique<TitleScene>();
	}

	return std::move(own);
}

void CustomMapScene::Draw()
{
	DrawString(100, 100, L"CustomMapScene", 0xffffff);

}
