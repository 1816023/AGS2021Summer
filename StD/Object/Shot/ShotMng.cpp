#include "ShotMng.h"

ShotMng::~ShotMng()
{
}

void ShotMng::Init(void)
{
}

void ShotMng::Update(float deltaTime)
{
}

void ShotMng::Draw(void)
{
}

void ShotMng::AddBullet(std::shared_ptr<Player> unit)
{
	shotList_.emplace_back(unit);
}

ShotMng::ShotMng()
{
}
