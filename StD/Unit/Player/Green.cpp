#include <DxLib.h>
#include "Green.h"

Green::Green()
{
}

Green::Green(Vec2Float pos, AttackType type)
{
	unitData =
		UnitData{ L"Blue",LoadGraph(L"data/image/Hexagon_Green.png"),1,
		UnitStat{ pos,15.0f,2.0f,6,10,false } };
	defaultPower_ = state_.power;
	isSkill_ = false;
	this->type = type;
	executable = false;
	coolTime_ = 600;
	UnitID = PlayerUnit::GREEN;
}

Green::~Green()
{
}

void Green::Init()
{
}

void Green::Draw()
{
	Vec2Int gSize;
	GetGraphSize(unitData.imageId, &gSize.x, &gSize.y);
	DrawGraph(unitData.stat.pos.x - gSize.x / 2, unitData.stat.pos.y - gSize.y / 2, unitData.imageId, true);
	auto gageMin = (unitData.stat.pos.x - gSize.x / 2);
	auto gageMax = (unitData.stat.pos.x + gSize.x / 2);
	DrawBox(gageMin, unitData.stat.pos.y - gSize.y, gageMax - gSize.x * (coolTime_ / 600), unitData.stat.pos.y - gSize.y + 10, 0xffffff, true);
	DrawBox(gageMin, unitData.stat.pos.y - gSize.y, unitData.stat.pos.x + gSize.x / 2, unitData.stat.pos.y - gSize.y + 10, 0xffffff, false);
	DrawFormatString(unitData.stat.pos.x, unitData.stat.pos.y + gSize.y, 0xffffff, L"HP:%d", unitData.stat.life);
	DrawFormatString(unitData.stat.pos.x, unitData.stat.pos.y + gSize.y + 20, 0xffffff, L"coolTime_:%f", coolTime_);
	DrawFormatString(unitData.stat.pos.x, unitData.stat.pos.y + gSize.y + 40, 0xffffff, L"power:%d", unitData.stat.power);
	DrawFormatString(unitData.stat.pos.x, unitData.stat.pos.y + gSize.y + 60, 0xffffff, L"type:%d", type);
	DrawFormatString(state_.pos.x, state_.pos.y + gSize.y + 80, 0xffffff, L"Skill:%s",(coolTime_ <= 0 ? L"OK":L"WAIT"));
}

void Green::Skill(void)
{
	state_.power = defaultPower_ * 1.5;
	if (coolTime_ <= -600)
	{
		executable = false;
		coolTime_ = 600;
		state_.power = defaultPower_;
	}
}

int Green::GetSpawnCost(void)
{
	return 8;
}
