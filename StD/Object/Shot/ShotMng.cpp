#include "ShotMng.h"
#include "../../Unit/Player/Yellow.h"

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
	for (auto& data : shotList_)
	{
		for (auto& bulletdata : shotList_[data.first])
		{
			DrawCircle(bulletdata.x, bulletdata.y, 5, 0xffffff, true);
		}
	}
}

void ShotMng::AddBullet(Player* ptr,Vec2Float pos)
{
	shotSpan_[ptr]--;
	if (shotSpan_[ptr] <= 0)
	{
		shotSpan_[ptr] = BASE_SPAN;
		shotList_[ptr].push_back(pos);
	}
}

void ShotMng::BulletMove(Player* ptr)
{
	//‚±‚Á‚±‚ÉŠp“x‚ð‹‚ß‚éŒvŽZ‚Ì‹Lq
	//UŒ‚”ÍˆÍ“à‚Ì“G‚ð’Tõ‚·‚éH
	//
	for (auto& bulletdata : shotList_[ptr])
	{
		bulletdata += Vec2Float(0.0f, 1.0f);
	}
}

ShotMng::ShotMng()
{
}
