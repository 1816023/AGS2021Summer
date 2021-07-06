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
	cnt = 0;

	IMAGE_ID(L"data/image/circle.png");
	IMAGE_ID(L"data/image/triangle.png");
	IMAGE_ID(L"data/image/pentagon.png");
	IMAGE_ID(L"data/image/square.png");
	shotMng_ = std::make_unique<ShotMng>();
	playerMng_ = std::make_unique<PlayerMng>();
	enemyMng_ = std::make_unique<EnemyManager>(*map);
	enemySpawner_.push_back(std::make_shared<EnemySpawner>(Vec2Float(64 * 10 - 32, 288), *enemyMng_));

	selectUnitId = PlayerUnit::NON;
	//enemySpawner_.push_back(std::make_shared<EnemySpawner>(Vec2Float(0, 100), enemyList));
}

GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	if (cnt++ < 60)
	{
		return std::move(own);
	}
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);

	auto delta = Application::Instance().GetDelta(); 

	UnitCreateFunc();

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

void GameScene::UnitCreateFunc()
{
	Vec2Int gSize;
	GetGraphSize(playerMng_->GetPlayerData()[PlayerUnit::YELLOW], &gSize.x, &gSize.y);

	auto mPos = Vec2Float(lpMouseController.GetOffsetPos().x, lpMouseController.GetOffsetPos().y);

	if (lpMouseController.GetClickTrg(MOUSE_INPUT_LEFT))
	{
		if (mPos.x >= DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 4)
		{
			auto tmpId = static_cast<PlayerUnit>(int((mPos.y + 10) / gSize.y) + 1);
			selectUnitId = (tmpId < PlayerUnit::MAX ? tmpId : selectUnitId);
		}
	}

	if (lpMouseController.GetClickUp(MOUSE_INPUT_LEFT))
	{
		if (map->GetMapChip(mPos) == MapChipName::FIELD)
		{
			Vec2Int chipPos = VecICast(mPos / map->GetChipSize());
			auto offSet = map->GetChipSize() / 2;
			playerMng_->Spawner(selectUnitId, VecFCast(chipPos * map->GetChipSize() + offSet));
		}
	}
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
	if (cnt < 60)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,cnt*4 );
	}
	map->Draw();
	shotMng_->Draw();
	playerMng_->Draw();
	enemyMng_->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameScene::DrawUI()
{
	DrawString(100, 100, L"GameScene", 0xffffff);
	// マウス座標
	VECTOR2 m_pos;
	GetMousePoint(&m_pos.x, &m_pos.y);
	DrawFormatString(m_pos.x - 5, m_pos.y - 5, 0x00ff00, L"%d", static_cast<int>(map->GetMapChip(m_pos)));
	DrawRotaGraph(m_pos.x, m_pos.y, 1, 0, playerMng_->GetPlayerData()[selectUnitId], true);
	int enemyRemain = 0;
	for (auto& spawners : enemySpawner_)
	{
		enemyRemain += spawners->GetRemainSpawnCnt();
	}
	enemyRemain += enemyMng_->GetEnemies().size();
	DrawFormatString(0, 0, 0xffffff, L"敵残存数 %d", enemyRemain);

	MenuDraw(m_pos);
}

void GameScene::MenuDraw(VECTOR2& m_pos)
{
	auto menuSize = Vec2Int(DEF_SCREEN_SIZE_X / 4, DEF_SCREEN_SIZE_Y);

	//menu画面
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawRoundRect(DEF_SCREEN_SIZE_X - menuSize.x-5, menuSize.y-5, DEF_SCREEN_SIZE_X-5, 5, 10, 10, 0x888888, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRoundRect(DEF_SCREEN_SIZE_X - menuSize.x-5, menuSize.y-5, DEF_SCREEN_SIZE_X-5, 5, 10, 10, 0xffffff, false);

	for (int data =1;data <=size_t(PlayerUnit::MAX);data++)
	{
		DrawGraph(DEF_SCREEN_SIZE_X - menuSize.x, (data-1)*64+10,playerMng_->GetPlayerData()[PlayerUnit(data)], true);
	}
	//ボタン
	DrawRoundRect(DEF_SCREEN_SIZE_X - menuSize.x + 15, menuSize.y - 18, DEF_SCREEN_SIZE_X - menuSize.x + 105, menuSize.y - 48, 10, 10, 0x000000, true);
	//ボタン縁
	DrawRoundRect(DEF_SCREEN_SIZE_X - menuSize.x + 10, menuSize.y - 20, DEF_SCREEN_SIZE_X - menuSize.x + 100, menuSize.y - 50, 10, 10, 0xffffff, true);
	//ボタン影
	DrawRoundRect(DEF_SCREEN_SIZE_X - menuSize.x + 10, menuSize.y - 20, DEF_SCREEN_SIZE_X - menuSize.x + 100, menuSize.y - 50, 10, 10, 0x000000, false);
	//ボタンテキスト
	DrawFormatString(DEF_SCREEN_SIZE_X - menuSize.x + 20, menuSize.y - 45, 0x000000, L"ユニット");
	
	//ボタン
	DrawRoundRect(DEF_SCREEN_SIZE_X - menuSize.x + 115, menuSize.y - 18, DEF_SCREEN_SIZE_X - menuSize.x + 205, menuSize.y - 48, 10, 10, 0x000000, true);
	//ボタン縁
	DrawRoundRect(DEF_SCREEN_SIZE_X - menuSize.x + 110, menuSize.y - 20, DEF_SCREEN_SIZE_X - menuSize.x + 200, menuSize.y - 50, 10, 10, 0xffffff, true);
	//ボタン影
	DrawRoundRect(DEF_SCREEN_SIZE_X - menuSize.x + 110, menuSize.y - 20, DEF_SCREEN_SIZE_X - menuSize.x + 200, menuSize.y - 50, 10, 10, 0x000000, false);
	//ボタンテキスト
	DrawFormatString(DEF_SCREEN_SIZE_X - menuSize.x + 120, menuSize.y-45, 0x000000, L"トラップ");

	//詳細表示
	if (m_pos.x >= DEF_SCREEN_SIZE_X - menuSize.x)
	{
		auto size_x = (m_pos.x + 200 <= DEF_SCREEN_SIZE_X ? 200 : -200);
		auto size_y = (m_pos.y <= DEF_SCREEN_SIZE_Y / 2 ? 100 : -100);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawRoundRect(m_pos.x, m_pos.y, m_pos.x + size_x, m_pos.y + size_y, 10, 10, 0x888888, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawRoundRect(m_pos.x, m_pos.y, m_pos.x + size_x, m_pos.y + size_y, 10, 10, 0xffffff, false);
	}
}
