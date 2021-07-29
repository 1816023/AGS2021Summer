#include "ShotMng.h"
#include <cmath>
#include <DxLib.h>
#include "../../Collision.h"
#include "../../Unit/Unit.h"
#include "../../Unit/Enemy/Enemy.h"
#include "../../Unit/Player/PlayerMng.h"
#include "../../Unit/Enemy/EnemyManager.h"
#include "../../Mng/SoundMng.h"

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
				lpSoundMng.StartSound("data/Sound/SE/pokopoko1.mp3", PlayType::BACK);
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

void ShotMng::BulletControler(float deltaTime, std::shared_ptr<PlayerMng> playerMng, std::shared_ptr<EnemyManager> enemyMng)
{

	auto unitList = playerMng->GetUnitList();
	auto enemyList = enemyMng->GetEnemies();

	//Player�̃��j�b�g�����˂����U���̊Ǘ�
	for (auto& unit : unitList)
	{
		auto type = unit->GetType();

		if (type == AttackType::NON)
		{
			//�U�����Ȃ����j�b�g�������玟��
			continue;
		}

		if (type == AttackType::SHOT)
		{
			for (auto enemy : enemyList)
			{
				if (this->isRange(enemy->GetPos(), unit->GetPos(), 64, 100 * unit->GetAtkRange()))
				{
					this->AddBullet(unit, enemy, deltaTime);
					auto shooter = this->BulletMove(unit, enemy, deltaTime);
					if (shooter != nullptr)
					{
						enemy->SetHP(shooter->GetAttackPower());
					}
					break;
				}
			}
		}

		if (type == AttackType::AREA)
		{
			//�N�[���^�C����ݒ肷�邱�Ƃŉ����H
			if (this->isCoolTime(unit, deltaTime))
			{
				for (auto enemy : enemyList)
				{
					if (this->isRange(enemy->GetPos(), unit->GetPos(), 64, 100 * unit->GetAtkRange()))
					{
						enemy->SetHP(unit->GetAttackPower());
					}
				}
			}
		}
	}

	//Enemy���̃��j�b�g�����˂����U���̊Ǘ�
	for (auto enemy : enemyList)
	{
		for (auto& unit : unitList)
		{

		}
	}
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
