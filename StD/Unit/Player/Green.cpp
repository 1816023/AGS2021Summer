#include <DxLib.h>
#include "Green.h"

Green::Green()
{
}

Green::Green(Vec2Float pos, AttackType type)
{
	imageID = LoadGraph(L"data/image/Hexagon_Green.png");
	state_ = UnitStat{ pos,15.0f,2.0f,6,10,false };
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

void Green::Update(float deltaTime)
{
	if (!executable)
	{
		coolTime_-= deltaTime;
		executable = (coolTime_ <= 0 ? true : false);
	}
	else
	{
		coolTime_++;
	}
}

void Green::Draw()
{
	Vec2Int gSize;
	GetGraphSize(imageID, &gSize.x, &gSize.y);
	DrawGraph(state_.pos.x-gSize.x/2, state_.pos.y-gSize.y/2,imageID,true);
	DrawFormatString(state_.pos.x, state_.pos.y + gSize.y, 0xffffff, L"HP:%d", state_.life);
	DrawFormatString(state_.pos.x, state_.pos.y + gSize.y + 20, 0xffffff, L"coolTime_:%f", coolTime_);
	DrawFormatString(state_.pos.x, state_.pos.y + gSize.y + 40, 0xffffff, L"power:%d", state_.power);
	DrawFormatString(state_.pos.x, state_.pos.y + gSize.y + 60, 0xffffff, L"type:%d", type);
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
