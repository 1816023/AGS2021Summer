#include "ETriangle.h"
#include "../../../Mng/ImageMng.h"
#include "../../../Map/Map.h"

ETriangle::ETriangle() : Enemy()
{

}

ETriangle::ETriangle(MapInfo& mapInfo) : Enemy(mapInfo)
{
	updater_ = &ETriangle::StartUpdate;
	// 三角の敵固有パラメータ設定
	state_.life = MID_HP;
	state_.power = LOW_ATK;
	enemyInfo_.speed = HIGH_SPEED;
}

ETriangle::~ETriangle()
{
}

void ETriangle::Update(float deltaTime)
{
	(this->*updater_)(deltaTime);
}

void ETriangle::Draw()
{
	DrawRotaGraph(state_.pos.x, state_.pos.y, enemyInfo_.scale, 0.0f, IMAGE_ID(L"data/image/triangle.png"), true);
	DrawFormatString(state_.pos.x, state_.pos.y + 8, 0xffffff, L"HP:%d", state_.life);
	DrawCircle(state_.pos.x, state_.pos.y, 5, 0xffffff, true);
}

Enemy* ETriangle::CreateClone()
{
	ETriangle* enemy = new ETriangle();
	enemy->updater_ = updater_;
	enemy->enemyInfo_ = enemyInfo_;
	enemy->state_ = state_;
	return enemy;
}

void ETriangle::StartUpdate(float deltaTime)
{
	SearchRoot(deltaTime);
	updater_ = &ETriangle::RunUpdate;
}

void ETriangle::RunUpdate(float deltaTime)
{
	Move(deltaTime);
	if (state_.life <= 0)
	{
		state_.isDead = true;
	}
}

void ETriangle::deathUpdate(float deltaTime)
{
}
