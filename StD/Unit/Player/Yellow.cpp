#include <DxLib.h>
#include "Yellow.h"

Yellow::Yellow()
{
}

Yellow::Yellow(Vec2Float pos, AttackType type)
{
	imageID = LoadGraph(L"data/image/Hexagon_Yellow.png");
	state_ = UnitStat{ pos,2,0.8f,10,20,false };
	isSkill_ = false;
	this->type = type;
	executable = false;
	coolTime_ = 600;
}

Yellow::~Yellow()
{
}

void Yellow::Init()
{
}

void Yellow::Draw()
{
	Vec2Int gSize;
	GetGraphSize(imageID, &gSize.x, &gSize.y);
	DrawGraph(state_.pos.x-gSize.x/2, state_.pos.y-gSize.y/2,imageID,true);
	DrawFormatString(state_.pos.x, state_.pos.y + gSize.y, 0xffffff, L"HP:%d", state_.life);
	DrawFormatString(state_.pos.x, state_.pos.y + gSize.y+20, 0xffffff, L"coolTime_:%f", coolTime_);
}

int Yellow::GetSpawnCost(void)
{
	return 5;
}

void Yellow::Skill(void)
{
	coolTime_--;
	if ((int)coolTime_ % 100 == 0)
	{
		state_.life += 2;
	}

	if (coolTime_ <= -600)
	{
		executable = false;
		coolTime_ = 600;
	}
}
