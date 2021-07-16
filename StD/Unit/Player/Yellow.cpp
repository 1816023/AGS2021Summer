#include <DxLib.h>
#include "Yellow.h"

Yellow::Yellow()
{
}

Yellow::Yellow(Vec2Float pos, AttackType type)
{
	unitData =
		UnitData{ L"Yellow",LoadGraph(L"data/image/Hexagon_Yellow.png"),1,
		UnitStat{ pos,2,0.8f,10,20,false }};
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
	GetGraphSize(unitData.imageId, &gSize.x, &gSize.y);
	DrawGraph(unitData.stat.pos.x - gSize.x / 2, unitData.stat.pos.y - gSize.y / 2, unitData.imageId, true);
	DrawFormatString(unitData.stat.pos.x, unitData.stat.pos.y + gSize.y, 0xffffff, L"HP:%d", unitData.stat.life);
	DrawFormatString(unitData.stat.pos.x, unitData.stat.pos.y + gSize.y+20, 0xffffff, L"coolTime_:%f", coolTime_);
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
		unitData.stat.life += 2;
	}

	if (coolTime_ <= -600)
	{
		executable = false;
		coolTime_ = 600;
	}
}
