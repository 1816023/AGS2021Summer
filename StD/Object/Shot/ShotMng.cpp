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
	Vec2Float pos = Vec2Float(0.0f, 0.0f);
	shotList_.emplace_back(BulletStatus{unit,pos});
}

void ShotMng::BulletMove(void)
{
	//こっこに角度を求める計算の記述


	for (auto& bulletdata : shotList_)
	{
		bulletdata.pos += Vec2Float(0.0f, 0.0f);
	}
}

ShotMng::ShotMng()
{
}
