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
			DrawCircle(bulletdata.first.x, bulletdata.first.y, 100, 0xff0000, false);
			DrawCircle(bulletdata.second.x, bulletdata.second.y, BASE_SIZE, 0xffffff, true);
		}
	}
}

void ShotMng::AddBullet(std::shared_ptr<Player> ptr,Vec2Float pos)
{
	shotSpan_[ptr]--;
	if (shotSpan_[ptr] <= 0)
	{
		shotSpan_[ptr] = BASE_SPAN;
		shotList_[ptr].push_back(std::make_pair(pos,pos));
	}
}

void ShotMng::BulletMove(std::shared_ptr<Player> ptr,Vec2Float pos)
{
	//こっこに角度を求める計算の記述
	auto ab = Vec2Float((pos.x - ptr->GetPos().x), (pos.y - ptr->GetPos().y));
	auto n = ab.Normarize();
	//攻撃範囲内の敵を探索する？
	if (!shotList_[ptr].empty())
	{
		for (auto itr = shotList_[ptr].begin(); itr != shotList_[ptr].end();)
		{
			if (isRange(pos, itr->second, 100*ptr->GetAtkRange(), BASE_SIZE))
			{
				//射程範囲内(弾を移動させる)
				itr->second += Vec2Float(n.x * ptr->GetBulletSpeed(), n.y*ptr->GetBulletSpeed());
				++itr;
			}
			else
			{
				//射程範囲外(リストから削除)
				itr = shotList_[ptr].erase(itr);
			}
		}
	}
}

bool ShotMng::isRange(Vec2Float unitPos, Vec2Float bulletPos,float unitSize,float bulletSize)
{
	//三平方の定理を使用した当たり判定(円と円)
	auto ab = Vec2Float(std::abs(unitPos.x - bulletPos.x), std::abs(unitPos.y - bulletPos.y));
	auto dist = std::sqrt((ab.x * ab.x) + (ab.y * ab.y));

	if (dist+(bulletSize*2)<=(unitSize + bulletSize))
	{
		//射程範囲内なのでtrue
		return true;
	}
	//射程範囲外なのでfalse
	return false;
}

ShotMng::ShotMng()
{
}
