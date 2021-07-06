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
			DrawCircle(bulletdata.first.x, bulletdata.first.y, BASE_SIZE, 0xffffff, true);
		}
	}
}

void ShotMng::AddBullet(std::shared_ptr<Unit> ptr, std::shared_ptr<Unit> target, float deltaTime)
{
	if (isCoolTime(ptr,deltaTime))
	{
		shotSpan_[ptr] = BASE_SPAN*ptr->GetAttackSpan();
		shotList_[ptr].push_back(std::make_pair(ptr->GetPos(),target));
	}
}

std::shared_ptr<Unit> ShotMng::BulletMove(std::shared_ptr<Unit> ptr, std::shared_ptr<Unit> target, float deltaTime)
{
	//�U���͈͓��̓G��T������H
	if (!shotList_[ptr].empty())
	{
		for (auto itr = shotList_[ptr].begin(); itr != shotList_[ptr].end();)
		{
			//�������Ɋp�x�����߂�v�Z�̋L�q
			auto ab = Vec2Float((itr->second->GetPos().x - ptr->GetPos().x), (itr->second->GetPos().y - ptr->GetPos().y));
			auto n = ab.Normarize();

			//�˒��͈͓�(�e���ړ�������)
			itr->first += Vec2Float(n.x * 15, n.y*15)* deltaTime;

			if (!isRange(itr->first, ptr->GetPos(), BASE_SIZE, 150))
			{
				//�˒��͈͊O(���X�g����폜)
				itr = shotList_[ptr].erase(itr);
				return nullptr;
			}

			if (isHitBvE(itr->first, BASE_SIZE, target->GetPos(), Vec2Float(60, 60)))
			{
				shooterPtr_ = ptr;
				//���������̂ō폜
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
	return nullptr;
}

void ShotMng::AreaAttackCtl(std::vector<std::shared_ptr<Unit>> unitList)
{
}

bool ShotMng::isRange(Vec2Float unitPos, Vec2Float shooterPos, float unitSize, float rangeSize)
{
	if (lpCollison.CvC(unitPos,unitSize,shooterPos,rangeSize))
	{
		//�˒��͈͓��Ȃ̂�true
		return true;
	}
	//�˒��͈͊O�Ȃ̂�false
	return false;
}

bool ShotMng::isCoolTime(std::shared_ptr<Unit> ptr, float deltaTime)
{
	shotSpan_[ptr]-=deltaTime;
	if (shotSpan_[ptr] <= 0)
	{
		shotSpan_[ptr] = BASE_SPAN * ptr->GetAttackSpan();
		return true;
	}
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
