#include "GameScene.h"
#include <DxLib.h>
#include "ResultScene.h"
#include "GameOverScene.h"
#include "../CustomDraw.h"
#include "../Application.h"
#include "../MouseController.h"
#include "../Object/Shot/ShotMng.h"
#include "../Unit/Player/Player.h"
#include "../Unit/Player/PlayerMng.h"
#include "../Unit/Enemy/EnemyManager.h"
#include "../Unit/Enemy/EnemySpawner.h"
#include "../Mng/ImageMng.h"
#include "../Unit/Enemy/Enemy.h"
#include "../Mng/SoundMng.h"

GameScene::GameScene()
{
	map = std::make_unique<Map>();
	map->SetUp("defalt_map");
	cnt = 0;
	waitFlag = false;
	resultFlag = true;
	accessData = nullptr;

	IMAGE_ID(L"data/image/circle.png");
	IMAGE_ID(L"data/image/triangle.png");
	IMAGE_ID(L"data/image/pentagon.png");
	IMAGE_ID(L"data/image/square.png");
	shotMng_ = std::make_unique<ShotMng>();
	playerMng_ = std::make_unique<PlayerMng>();
	enemyMng_ = std::make_unique<EnemyManager>(*map);
	enemySpawner_.push_back(std::make_shared<EnemySpawner>(Vec2Float(64 * 10 - 32, 288), *enemyMng_, *map));

	selectUnitId = PlayerUnit::NON;
	//enemySpawner_.push_back(std::make_shared<EnemySpawner>(Vec2Float(0, 100), enemyList));
}

GameScene::GameScene(std::string mapName)
{
	map = std::make_unique<Map>();
	map->SetUp(mapName);
	cnt = 0;
	waitFlag = false;
	resultFlag = true;
	accessData = nullptr;

	IMAGE_ID(L"data/image/circle.png");
	IMAGE_ID(L"data/image/triangle.png");
	IMAGE_ID(L"data/image/pentagon.png");
	IMAGE_ID(L"data/image/square.png");
	shotMng_ = std::make_unique<ShotMng>();
	playerMng_ = std::make_shared<PlayerMng>();
	enemyMng_ = std::make_shared<EnemyManager>(*map);
	enemySpawner_.push_back(std::make_shared<EnemySpawner>(Vec2Float(64 * 10 - 32, 288), *enemyMng_, *map));

	selectUnitId = PlayerUnit::NON;
	lpSoundMng.StartSound("data/Sound/SE/BGM3.mp3", PlayType::LOOP);
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

	float delta = Application::Instance().GetDelta(); 

	UnitCreateFunc();

	//待機状態なら以後の処理を行わず戻す
	if (waitFlag)
	{
		UnitAccessFunc();
		return std::move(own);
	}

	playerMng_->Update(delta, shotMng_->GetShooterPtr());

	shotMng_->BulletControler(delta,playerMng_,enemyMng_);

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
		resultFlag = true;
		lpSoundMng.StopSound("data/Sound/SE/BGM3.mp3");
		return std::make_unique<ResultScene>(resultFlag);
	}
	if (enemyMng_->IsGoal() == true)
	{
		resultFlag = false;
		lpSoundMng.StopSound("data/Sound/SE/BGM3.mp3");
		return std::make_unique<ResultScene>(resultFlag);
	}
	return std::move(own);
}

void GameScene::UnitCreateFunc()
{
	Vec2Int gSize;
	GetGraphSize(playerMng_->GetPlayerData()[PlayerUnit::YELLOW].imageId, &gSize.x, &gSize.y);

	auto mPos = VecFCast(lpMouseController.GetOffsetPos());

	if (lpMouseController.GetClickTrg(MOUSE_INPUT_LEFT))
	{
		if (mPos.x >= DEF_SCREEN_SIZE_X - DEF_SCREEN_SIZE_X / 4)
		{
			auto tmpId = static_cast<PlayerUnit>(int((mPos.y + 10) / gSize.y) + 1);
			selectUnitId = (tmpId < PlayerUnit::MAX ? tmpId : selectUnitId);
		}
	}

	Vec2Int chipPos = VecICast(mPos / map->GetChipSize());
	auto offSet = map->GetChipSize() / 2;

	if (lpMouseController.GetClickUp(MOUSE_INPUT_RIGHT))
	{
		for (auto data : playerMng_->GetUnitList())
		{
			data->SetStatusOpen(false);
		}

		//右クリックしたマスに配置されているユニットの取得
		accessData = playerMng_->GetUnitData(VecFCast(chipPos * map->GetChipSize() + offSet));
		if (accessData != nullptr)
		{
			waitFlag = true;
			accessData->SetStatusOpen(true);
		}
	}

	if (lpMouseController.GetClickUp(MOUSE_INPUT_LEFT))
	{
		for (auto data : playerMng_->GetUnitList())
		{
			data->SetStatusOpen(false);
		}

		auto unitData = playerMng_->GetUnitData(VecFCast(chipPos * map->GetChipSize() + offSet));
		if (map->GetMapChip(mPos) == MapChipName::FIELD && unitData == nullptr)
		{
			playerMng_->Spawner(selectUnitId, VecFCast(chipPos * map->GetChipSize() + offSet));
		}
	}
}

void GameScene::UnitAccessFunc(void)
{
	if (accessData == nullptr)
	{
		return;
	}
	
	if (lpMouseController.GetClickUp(MOUSE_INPUT_LEFT))
	{
		if (lpMouseController.IsHitBoxToMouse(VecICast(lpCustomDraw.GetDrawData(L"レベルアップ").first), VecICast(lpCustomDraw.GetDrawData(L"レベルアップ").second)))
		{
			playerMng_->SetCost(playerMng_->GetCost() - accessData->GetLevelUpCost());
			accessData->LevelShift(1);
			waitFlag = false;
		}

		if (accessData->GetCoolTime() <= 0)
		{
			if (lpMouseController.IsHitBoxToMouse(VecICast(lpCustomDraw.GetDrawData(L"スキル発動").first), VecICast(lpCustomDraw.GetDrawData(L"スキル発動").second)))
			{
				accessData->SetExecutable(true);
				waitFlag = false;
			}
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
	DrawRotaGraph(m_pos.x, m_pos.y, 1, 0, playerMng_->GetPlayerData()[selectUnitId].imageId, true);
	int enemyRemain = 0;
	for (auto& spawners : enemySpawner_)
	{
		enemyRemain += spawners->GetRemainSpawnCnt();
	}
	enemyRemain += enemyMng_->GetEnemies().size();
	DrawFormatString(0, 32, 0xffffff, L"敵残存数 %d", enemyRemain);

	MenuDraw(m_pos);
}

void GameScene::MenuDraw(VECTOR2& m_pos)
{
	auto menuSize = Vec2Int(-DEF_SCREEN_SIZE_X / 4, DEF_SCREEN_SIZE_Y);

	//menu画面
	lpCustomDraw.MakeRoundRect(Vec2Float(DEF_SCREEN_SIZE_X,0), menuSize, Vec2Float(0, 0), 0x555555, 200, true);

	for (int data =1;data <=size_t(PlayerUnit::MAX);data++)
	{
		DrawGraph(DEF_SCREEN_SIZE_X + menuSize.x, (data-1)*64+10,playerMng_->GetPlayerData()[PlayerUnit(data)].imageId, true);
		if (data < size_t(PlayerUnit::MAX))
		{
			DrawFormatString(DEF_SCREEN_SIZE_X + menuSize.x + 64, (data - 1) * 64 + 10, 0xffffff, playerMng_->GetPlayerData()[PlayerUnit(data)].name);
		}
	}

	for (auto data : playerMng_->GetUnitList())
	{
		Vec2Float localPos = data->GetPos();
		if (data->isStatusOpen())
		{
			lpCustomDraw.MakeRoundRect(localPos, Vec2Int(250, -128), Vec2Float(-32, -32), 0x555555, 200, true);
			lpCustomDraw.MakeRoundButton(localPos,Vec2Int(100,24),Vec2Float(-27,-64),0xffffff,0x000000,L"スキル発動");
			lpCustomDraw.MakeRoundButton(localPos,Vec2Int(100,24),Vec2Float(100,-64),0xffffff,0x000000,L"レベルアップ");

			data->StatusDraw(Vec2Float(localPos.x-32, localPos.y-128-32));
		}
	}
	lpCustomDraw.MakeRoundButton(Vec2Float(DEF_SCREEN_SIZE_X, DEF_SCREEN_SIZE_Y),Vec2Int(80,16),Vec2Float(-DEF_SCREEN_SIZE_X / 4+15,-30),0xffffff,0x000000,L"ユニット");
	lpCustomDraw.MakeRoundButton(Vec2Float(DEF_SCREEN_SIZE_X, DEF_SCREEN_SIZE_Y),Vec2Int(80,16),Vec2Float(-DEF_SCREEN_SIZE_X / 4+115,-30),0xffffff,0x000000,L"トラップ");

	PlayerUnit id = PlayerUnit(((m_pos.y-10) / 64)+1);
	//詳細表示
	if (m_pos.x >= DEF_SCREEN_SIZE_X +menuSize.x && id < PlayerUnit::MAX)
	{
		lpCustomDraw.MakeRoundRect(VecFCast(m_pos), Vec2Int(-200,100), Vec2Float(0,0), 0x555555, 200, true);

		auto size_x = -200;
		auto size_y = 100;

		if (id != PlayerUnit::NON)
		{
			DrawFormatString(m_pos.x + size_x + 4, m_pos.y + 4, 0xffffff, L"初期Lv：%d", playerMng_->GetPlayerData()[id].lv);
			DrawFormatString(m_pos.x + size_x + 4, m_pos.y + 4 + 16, 0xffffff, L"HP：%d", playerMng_->GetPlayerData()[id].stat.life);
			DrawFormatString(m_pos.x + size_x + 4 + 96, m_pos.y + 4 + 16, 0xffffff, L"攻撃力：%d", playerMng_->GetPlayerData()[id].stat.power);
		}
	}
}
