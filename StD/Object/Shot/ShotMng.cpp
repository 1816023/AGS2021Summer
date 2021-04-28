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

void ShotMng::AddBullet(Player* ptr,Vec2Float pos)
{
	shotSpan_[ptr]--;
	if (shotSpan_[ptr] <= 0)
	{
		shotSpan_[ptr] = BASE_SPAN;
		shotList_[ptr].push_back(std::make_pair(pos,pos));
	}
}

void ShotMng::BulletMove(Player* ptr)
{
	//�������Ɋp�x�����߂�v�Z�̋L�q
	//�U���͈͓��̓G��T������H
	//
	if (!shotList_[ptr].empty())
	{
		for (auto itr = shotList_[ptr].begin(); itr != shotList_[ptr].end();)
		{
			if (isRange(itr->first, itr->second, 100, BASE_SIZE))
			{
				//�˒��͈͓�(�e���ړ�������)
				itr->second += Vec2Float(0.0f, 1.0f);
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
	//�O�����̒藝���g�p���������蔻��(�~�Ɖ~)
	auto ab = Vec2Float(std::abs(unitPos.x - bulletPos.x), std::abs(unitPos.y - bulletPos.y));
	auto dist = std::sqrt((ab.x * ab.x) + (ab.y * ab.y));

	if (dist+(bulletSize*2)<=(unitSize + bulletSize))
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
