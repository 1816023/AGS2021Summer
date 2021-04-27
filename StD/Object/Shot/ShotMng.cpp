#include "ShotMng.h"
#include <cmath>
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
		//if (isRange())
		//{
			bulletdata += Vec2Float(0.0f, 5.0f);
		//}
	}
}

bool ShotMng::isRange(Vec2Float unitPos, Vec2Float bulletPos,float unitSize,float bulletSize)
{
	auto ab = Vec2Float(std::abs(unitPos.x - bulletPos.x), std::abs(unitPos.y - bulletPos.y));
	auto dist = std::sqrt((ab.x * ab.x) + (ab.y * ab.y));
	if (dist<=(unitSize + bulletSize))
	{
		return true;
	}
	return false;
}

ShotMng::ShotMng()
{
}
