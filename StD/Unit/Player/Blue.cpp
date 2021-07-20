#include <DxLib.h>
#include "Blue.h"

Blue::Blue()
{
}

Blue::Blue(Vec2Float pos, AttackType type)
{
	unitData = 
		UnitData{L"Blue",LoadGraph(L"data/image/Hexagon_Blue.png"),1,1,
		UnitStat{ pos,2,0.8f,20,20,false } };
	isSkill_ = false;
	this->type = type;
	executable = false;
	coolTime_ = 300;
}

Blue::~Blue()
{
}

void Blue::Init()
{
}

void Blue::Draw()
{
	Vec2Int gSize;
	GetGraphSize(unitData.imageId, &gSize.x, &gSize.y);
	DrawGraph(unitData.stat.pos.x-gSize.x/2, unitData.stat.pos.y-gSize.y/2,unitData.imageId,true);
	DrawCircle(unitData.stat.pos.x, unitData.stat.pos.y,150, 0xff0000, false);
	auto gageMin = (unitData.stat.pos.x - gSize.x / 2);
	auto gageMax = (unitData.stat.pos.x + gSize.x / 2);
	DrawBox(gageMin, unitData.stat.pos.y - gSize.y, gageMax - gSize.x *(coolTime_/600), unitData.stat.pos.y - gSize.y + 10, 0xffffff, true);
	DrawBox(gageMin, unitData.stat.pos.y - gSize.y, unitData.stat.pos.x + gSize.x / 2, unitData.stat.pos.y - gSize.y + 10, 0xffffff, false);
	DrawFormatString(unitData.stat.pos.x, unitData.stat.pos.y + gSize.y, 0xffffff, L"HP:%d", unitData.stat.life);
	DrawFormatString(unitData.stat.pos.x, unitData.stat.pos.y + gSize.y + 20, 0xffffff, L"coolTime_:%f", coolTime_);
	DrawFormatString(unitData.stat.pos.x, unitData.stat.pos.y + gSize.y + 40, 0xffffff, L"power:%d", unitData.stat.power);
	DrawFormatString(unitData.stat.pos.x, unitData.stat.pos.y + gSize.y + 60, 0xffffff, L"type:%d", type);
}

void Blue::Skill(void)
{
	if (type != AttackType::AREA)
	{
		type = AttackType::AREA;
		unitData.stat.power = unitData.stat.power * 1.5;
	}
	
	if (coolTime_ >= 600)
	{
		executable = false;
		type = AttackType::SHOT;
		unitData.stat.power = unitData.stat.power / 1.5;
		coolTime_ = 600;
	}
}

int Blue::GetSpawnCost(void)
{
	return 12;
}

//void Blue::Skill(void)
//{
//	stat_.life += 10;
//}
