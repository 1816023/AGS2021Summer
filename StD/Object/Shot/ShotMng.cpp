#include "ShotMng.h"
#include <cmath>
#include <DxLib.h>
#include "../../Collision.h"
#include "../../Unit/Unit.h"

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
			DrawCircle(bulletdata.first.x, bulletdata.first.y, 80, 0xff0000, false);
			DrawCircle(bulletdata.second.x, bulletdata.second.y, BASE_SIZE, 0xffffff, true);
		}
	}
}

void ShotMng::AddBullet(std::shared_ptr<Unit> ptr,Vec2Float pos)
{
	shotSpan_[ptr]--;
	if (shotSpan_[ptr] <= 0)
	{
		shotSpan_[ptr] = BASE_SPAN;
		shotList_[ptr].push_back(std::make_pair(pos,pos));
	}
}

std::shared_ptr<Unit> ShotMng::BulletMove(std::shared_ptr<Unit> ptr,Vec2Float pos)
{
	//こっこに角度を求める計算の記述
	auto ab = Vec2Float((pos.x - ptr->GetPos().x), (pos.y - ptr->GetPos().y));
	auto n = ab.Normarize();
	//攻撃範囲内の敵を探索する？
	if (!shotList_[ptr].empty())
	{
		for (auto itr = shotList_[ptr].begin(); itr != shotList_[ptr].end();)
		{
				//射程範囲内(弾を移動させる)
				itr->second += Vec2Float(n.x * ptr->GetBulletSpeed(), n.y*ptr->GetBulletSpeed());
				if (isHitBvE(itr->second, BASE_SIZE, pos, Vec2Float(60, 60)))
				{
					shooterPtr_ = ptr;
					//射程範囲外(リストから削除)
					itr = shotList_[ptr].erase(itr);
					return shooterPtr_ = ptr;
				}
				else
				{
					shooterPtr_ = nullptr;
					++itr;
				}
		}
	}
}

bool ShotMng::isRange(Vec2Float unitPos, Vec2Float shooterPos, float unitSize, float rangeSize)
{
	if (lpCollison.CvC(unitPos,unitSize,shooterPos,rangeSize))
	{
		//射程範囲内なのでtrue
		return true;
	}
	//射程範囲外なのでfalse
	return false;
}

bool ShotMng::isHitBvE(Vec2Float bulletPos,float bulletSize,Vec2Float unitPos,Vec2Float unitSize)
{
	auto size = Vec2Float(unitSize.x / 2, unitSize.y / 2);
	if (lpCollison.CvB(bulletPos, bulletSize, unitPos, size))
	{
		return true;
	}
	return false;
}

ShotMng::ShotMng()
{
	shooterPtr_ = nullptr;
}
