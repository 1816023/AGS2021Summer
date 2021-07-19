#include "ESquare.h"
#include "../../../Mng/ImageMng.h"
#include "../../../Map/Map.h"

ESquare::ESquare() : Enemy()
{
	updater_ = &ESquare::StartUpdate;
}

ESquare::ESquare(MapInfo& mapInfo) : Enemy(mapInfo)
{
	updater_ = &ESquare::StartUpdate;
	// 三角の敵固有パラメータ設定
	state_.life = HIGH_HP;
	state_.power = MID_ATK;
	enemyInfo_.speed = LOW_SPEED;
}

ESquare::~ESquare()
{
}

void ESquare::Update(float deltaTime)
{
	(this->*updater_)(deltaTime);
}

void ESquare::Draw()
{
	DrawRotaGraphF(state_.pos.x, state_.pos.y, enemyInfo_.scale, 0.0f, IMAGE_ID(L"data/image/square.png"), true);
	DrawFormatStringF(state_.pos.x, state_.pos.y + 8, 0xffffff, L"HP:%d", state_.life);
	DrawCircle(static_cast<int>(state_.pos.x), static_cast<int>(state_.pos.y), 5, 0xffffff, true);
}

Enemy* ESquare::CreateClone()
{
	ESquare* enemy = new ESquare();
	enemy->updater_ = updater_;
	enemy->enemyInfo_ = enemyInfo_;
	enemy->state_ = state_;
	return enemy;
}

void ESquare::StartUpdate(float deltaTime)
{
	SearchRoot(deltaTime);
	updater_ = &ESquare::RunUpdate;
}

void ESquare::RunUpdate(float deltaTime)
{
	Move(deltaTime);
	if (state_.life <= 0)
	{
		state_.isDead = true;
	}
}

void ESquare::deathUpdate(float deltaTime)
{
}
