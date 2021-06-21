#include <DxLib.h>
#include "Blue.h"

Blue::Blue()
{
}

Blue::Blue(Vec2Float pos, AttackType type)
{
	imageID = LoadGraph(L"data/image/Hexagon_Blue.png");
	state_ = UnitStat{ pos,2,0.8f,20,20,false };
	isSkill_ = false;
	this->type = type;
	executable = false;
	coolTime_ = 0;
}

Blue::~Blue()
{
}

void Blue::Init()
{
}

void Blue::Update(float deltaTime)
{
	coolTime_--;
	if (!executable)
	{
		executable = (coolTime_ <= 0 ? true : false);
	}
}

void Blue::Draw()
{
	Vec2Int gSize;
	GetGraphSize(imageID, &gSize.x, &gSize.y);
	DrawGraph(state_.pos.x-gSize.x/2, state_.pos.y-gSize.y/2,imageID,true);
	DrawCircle(state_.pos.x, state_.pos.y,150, 0xff0000, false);
	auto gageMin = (state_.pos.x - gSize.x / 2);
	auto gageMax = (state_.pos.x + gSize.x / 2);
	DrawBox(state_.pos.x - gSize.x / 2, state_.pos.y - gSize.y, gageMin - gSize.x *(coolTime_/600), state_.pos.y - gSize.y + 10, 0xffffff, true);
	DrawBox(state_.pos.x - gSize.x / 2, state_.pos.y - gSize.y, state_.pos.x + gSize.x / 2, state_.pos.y - gSize.y + 10, 0xffffff, false);
	DrawFormatString(state_.pos.x, state_.pos.y + gSize.y, 0xffffff, L"HP:%d", state_.life);
	DrawFormatString(state_.pos.x, state_.pos.y + gSize.y + 20, 0xffffff, L"coolTime_:%f", coolTime_);
	DrawFormatString(state_.pos.x, state_.pos.y + gSize.y + 40, 0xffffff, L"power:%d", state_.power);
	DrawFormatString(state_.pos.x, state_.pos.y + gSize.y + 60, 0xffffff, L"type:%d", type);
}

void Blue::Skill(void)
{
	if (type != AttackType::AREA)
	{
		type = AttackType::AREA;
		state_.power = state_.power * 1.5;
	}
	
	if (coolTime_ <= -600)
	{
		executable = false;
		type = AttackType::SHOT;
		state_.power = state_.power / 1.5;
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
