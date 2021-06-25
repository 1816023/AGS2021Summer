#include "ESquare.h"
#include "../../../Mng/ImageMng.h"
#include "../../../Map/Map.h"

ESquare::ESquare() : Enemy()
{

}

ESquare::ESquare(MapInfo& mapInfo) : Enemy(mapInfo)
{
	updater_ = &ESquare::StartUpdate;
	// 三角の敵固有パラメータ設定
	state_.life = MID_HP;
	state_.power = LOW_ATK;
	enemyInfo_.speed = HIGH_SPEED;
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
	DrawRotaGraph(state_.pos.x, state_.pos.y, enemyInfo_.scale, 0.0f, IMAGE_ID(L"data/image/square.png"), true);
	DrawFormatString(state_.pos.x, state_.pos.y + 8, 0xffffff, L"HP:%d", state_.life);
	DrawCircle(state_.pos.x, state_.pos.y, 5, 0xffffff, true);
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
	if (state_.isDead)
	{
		state_.isDead = true;
	}
}

void ESquare::deathUpdate(float deltaTime)
{
}
