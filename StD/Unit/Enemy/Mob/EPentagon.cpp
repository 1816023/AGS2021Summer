#include "EPentagon.h"
#include "../../../Mng/ImageMng.h"
#include "../../../Map/Map.h"

EPentagon::EPentagon() : Enemy()
{
	updater_ = &EPentagon::StartUpdate;
}

EPentagon::EPentagon(MapInfo& mapInfo) : Enemy(mapInfo)
{
	updater_ = &EPentagon::StartUpdate;
	// 五角形の敵固有パラメータ設定
	state_.life = LOW_HP;
	state_.power = HIGH_ATK;
	enemyInfo_.speed = MID_SPEED;
}

EPentagon::~EPentagon()
{
}

void EPentagon::Update(float deltaTime)
{
	(this->*updater_)(deltaTime);
}

void EPentagon::Draw()
{
	DrawRotaGraph(state_.pos.x, state_.pos.y, enemyInfo_.scale, 0.0f, IMAGE_ID(L"data/image/pentagon.png"), true);
	DrawFormatString(state_.pos.x, state_.pos.y + 8, 0xffffff, L"HP:%d", state_.life);
	DrawCircle(state_.pos.x, state_.pos.y, 5, 0xffffff, true);
}

Enemy* EPentagon::CreateClone()
{
	EPentagon* enemy = new EPentagon();
	enemy->updater_ = updater_;
	enemy->enemyInfo_ = enemyInfo_;
	enemy->state_ = state_;
	return enemy;
}

void EPentagon::StartUpdate(float deltaTime)
{
	SearchRoot(deltaTime);
	updater_ = &EPentagon::RunUpdate;
}

void EPentagon::RunUpdate(float deltaTime)
{
	Move(deltaTime);
	if (state_.isDead)
	{
		state_.isDead = true;
	}
}

void EPentagon::deathUpdate(float deltaTime)
{
}

