#include "ECircle.h"
#include "../../../Mng/ImageMng.h"
#include "../../../Map/Map.h"

ECircle::ECircle() : Enemy()
{
	updater_ = &ECircle::StartUpdate;
}

ECircle::ECircle(MapInfo& mapInfo):Enemy(mapInfo)
{
	updater_ = &ECircle::StartUpdate;
	// 円の敵固有パラメータ設定
	state_.life = MID_HP;
	enemyInfo_.speed = MID_SPEED;
}

ECircle::~ECircle()
{
}

void ECircle::Update(float deltaTime)
{
	(this->*updater_)(deltaTime);
}

void ECircle::Draw()
{
	DrawRotaGraphF(state_.pos.x, state_.pos.y, enemyInfo_.scale, 0.0f, IMAGE_ID(L"data/image/circle.png"), true);
	DrawFormatStringF(state_.pos.x, state_.pos.y +8, 0xffffff, L"HP:%d", state_.life);
	DrawCircle(static_cast<int>(state_.pos.x), static_cast<int>(state_.pos.y), 5, 0xffffff, true);
}

Enemy* ECircle::CreateClone()
{
	ECircle* enemy = new ECircle();
	enemy->updater_ = updater_;
	enemy->enemyInfo_ = enemyInfo_;
	enemy->state_ = state_;
	return enemy;
}

void ECircle::StartUpdate(float deltaTime)
{
	SearchRoot(deltaTime);
	updater_ = &ECircle::RunUpdate;
}

void ECircle::RunUpdate(float deltaTime)
{
	Move(deltaTime);
	if (state_.life <= 0)
	{
		state_.isDead = true;
	}
}

void ECircle::deathUpdate(float deltaTime)
{
}

