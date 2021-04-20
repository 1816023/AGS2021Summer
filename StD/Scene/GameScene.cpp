#include "GameScene.h"
#include "../Unit/Player/PlayerMng.h"
#include <DxLib.h>
#include "ResultScene.h"
#include "../Application.h"
#include "../Unit/Enemy/EnemyManager.h"
#include "../Unit/Enemy/EnemySpawner.h"

GameScene::GameScene()
{
	map = std::make_unique<Map>();
	map->SetUp("defalt_map");

	std::vector<EnemyType>enemyList;
	for (int i = 0; i < 50; i++)
	{
		enemyList.emplace_back(EnemyType::Circle);
	}

	enemySpawner_ .push_back(std::make_shared<EnemySpawner>(Vec2Float(100, 100), enemyList));
	enemySpawner_ .push_back(std::make_shared<EnemySpawner>(Vec2Float(0, 100), enemyList));
	lpPlayerMng.Spawner(PlayerUnit::YELLOW);
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
	auto delta = Application::Instance().getDelta();
	for (auto& spawners : enemySpawner_)
	{
		spawners->Update(delta);
	}
	EnemyManager::Instance().Update(delta);
	return std::move(own);
}

void GameScene::Draw()
{
	EnemyManager::Instance().Draw();
	map->Draw();
}

void GameScene::DrawUI()
{
	DrawString(100, 100, L"GameScene", 0xffffff);
	// マウス座標
	VECTOR2 m_pos;
	GetMousePoint(&m_pos.x, &m_pos.y);
	DrawFormatString(m_pos.x - 5, m_pos.y - 5, 0x00ff00, L"%d", static_cast<int>(map->GetMapChip(m_pos)));
}
