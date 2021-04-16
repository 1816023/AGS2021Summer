#include "GameScene.h"
#include <DxLib.h>
#include "ResultScene.h"

GameScene::GameScene()
{
	map = std::make_unique<Map>();
	map->SetUp("defalt_map");
}

GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);

	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE]))
	{
		return std::make_unique<ResultScene>();
	}

	return std::move(own);
}

void GameScene::Draw()
{
	DrawString(100, 100, L"GameScene", 0xffffff);
	map->Draw();
	VECTOR2 m_pos;
	GetMousePoint(&m_pos.x, &m_pos.y);
	DrawFormatString(m_pos.x-5,m_pos.y-5,0x00ff00,L"%d",static_cast<int>( map->GetMapChip(m_pos)));
}
