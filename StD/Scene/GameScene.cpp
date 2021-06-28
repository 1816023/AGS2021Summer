#include "GameScene.h"
#include <DxLib.h>
#include "ResultScene.h"
#include "GameOverScene.h"
#include "../Application.h"
#include "../MouseController.h"
#include "../Object/Shot/ShotMng.h"
#include "../Unit/Player/PlayerMng.h"
#include "../Unit/Enemy/EnemyManager.h"
#include "../Unit/Enemy/EnemySpawner.h"
#include "../Mng/ImageMng.h"
#include "../Unit/Enemy/Enemy.h"

GameScene::GameScene()
{
	map = std::make_unique<Map>();
	map->SetUp("defalt_map");

	IMAGE_ID(L"data/image/circle.png");
	shotMng_ = std::make_unique<ShotMng>();
	playerMng_ = std::make_unique<PlayerMng>();
	enemyMng_ = std::make_unique<EnemyManager>(*map);
	enemySpawner_.push_back(std::make_shared<EnemySpawner>(Vec2Float(32, 224), *enemyMng_));
	//enemySpawner_.push_back(std::make_shared<EnemySpawner>(Vec2Float(0, 100), enemyList));
}

GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);

	auto delta = Application::Instance().GetDelta();

	if (lpMouseController.GetClickTrg(MOUSE_INPUT_LEFT))
	{
		playerMng_->Spawner(PlayerUnit::BLUE, Vec2Float(lpMouseController.GetOffsetPos().x, lpMouseController.GetOffsetPos().y));
	}

	playerMng_->Update(delta, shotMng_->GetShooterPtr());
	BulletControler();

	int spawnRemain = 0;
	for (auto& spawners : enemySpawner_)
	{
		spawners->Update(delta);
		spawnRemain += spawners->GetRemainSpawnCnt();
	}
	enemyMng_->Update(delta);


	for (auto enemy : enemyMng_->GetEnemies())
	{
		if (enemy == nullptr)
		{
			break;
		}
		if (enemy->IsDeath())
		{
			enemyMng_->Killer(enemy);
		}
	}

	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE])
		|| spawnRemain == 0 && enemyMng_->GetEnemies().size() == 0)
	{
		return std::make_unique<ResultScene>();
	}
	if (enemyMng_->IsGoal() == true)
	{
		return std::make_unique<GameOverScene>();
	}
	return std::move(own);
}

void GameScene::BulletControler(void)
{
	auto unitList = playerMng_->GetUnitList();
	auto enemyList = enemyMng_->GetEnemies();

	//Playerのユニットが発射した攻撃の管理
	for (auto& unit : unitList)
	{
		auto type = unit->GetType();

		if (type == AttackType::NON)
		{
			//攻撃しないユニットだったら次へ
			continue;
		}

		if (type == AttackType::SHOT)
		{
			for (auto enemy : enemyList)
			{
				if (shotMng_->isRange(enemy->GetPos(), unit->GetPos(), 64, 100 * unit->GetAtkRange()))
				{
					shotMng_->AddBullet(unit, enemy);
					auto shooter = shotMng_->BulletMove(unit, enemy);
					if (shooter != nullptr)
					{
						enemy->SetHP(shooter->GetAttackPower());
					}
					break;
				}
			}
		}

		if (type == AttackType::AREA)
		{
			//クールタイムを設定することで解決？
			if (shotMng_->isCoolTime(unit))
			{
				for (auto enemy : enemyList)
				{
					if (shotMng_->isRange(enemy->GetPos(), unit->GetPos(), 64, 100 * unit->GetAtkRange()))
					{
						enemy->SetHP(unit->GetAttackPower());
					}
				}
			}
		}
	}

	//Enemy側のユニットが発射した攻撃の管理
	for (auto enemy : enemyList)
	{
		for (auto& unit : unitList)
		{

		}
	}
}

void GameScene::Draw()
{
	map->Draw();
	shotMng_->Draw();
	playerMng_->Draw();
	enemyMng_->Draw();
}

void GameScene::DrawUI()
{
	DrawString(100, 100, L"GameScene", 0xffffff);
	// マウス座標
	VECTOR2 m_pos;
	GetMousePoint(&m_pos.x, &m_pos.y);
	DrawFormatString(m_pos.x - 5, m_pos.y - 5, 0x00ff00, L"%d", static_cast<int>(map->GetMapChip(m_pos)));
}
