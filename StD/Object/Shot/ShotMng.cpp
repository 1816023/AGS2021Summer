#include "ShotMng.h"
#include <cmath>
#include "../../Collision.h"
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
	//�������Ɋp�x�����߂�v�Z�̋L�q
	auto ab = Vec2Float((pos.x - ptr->GetPos().x), (pos.y - ptr->GetPos().y));
	auto n = ab.Normarize();
	//�U���͈͓��̓G��T������H
	if (!shotList_[ptr].empty())
	{
		for (auto itr = shotList_[ptr].begin(); itr != shotList_[ptr].end();)
		{
			if (isRange(pos, itr->second, 100*ptr->GetAtkRange(), BASE_SIZE))
			{
				//�˒��͈͓�(�e���ړ�������)
				itr->second += Vec2Float(n.x * ptr->GetBulletSpeed(), n.y*ptr->GetBulletSpeed());
				++itr;
			}
			else
			{
				//�˒��͈͊O(���X�g����폜)
				itr = shotList_[ptr].erase(itr);
			}
		}
	}
}

bool ShotMng::isRange(Vec2Float unitPos, Vec2Float bulletPos,float unitSize,float bulletSize)
{
	if (lpCollison.CvC(unitPos,unitSize,bulletPos,bulletSize))
	{
		//�˒��͈͓��Ȃ̂�true
		return true;
	}
	//�˒��͈͊O�Ȃ̂�false
	return false;
}

ShotMng::ShotMng()
{
}
