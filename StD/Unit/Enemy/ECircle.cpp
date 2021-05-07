#include "ECircle.h"
#include "../../Mng/ImageMng.h"
#include "../../Map/Map.h"

ECircle::ECircle() : Enemy()
{
	
}

ECircle::ECircle(MapInfo& mapInfo):Enemy(mapInfo)
{
	updater_ = &ECircle::StartUpdate;
	// ‰~‚Ì“GŒÅ—Lƒpƒ‰ƒ[ƒ^Ý’è
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
	DrawRotaGraph(state_.pos.x, state_.pos.y, enemyInfo_.scale, 0.0f, IMAGE_ID(L"data/image/circle.png"), true);
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

