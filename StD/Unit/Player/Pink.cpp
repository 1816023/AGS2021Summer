#include <DxLib.h>
#include "PlayerMng.h"
#include "Pink.h"

Pink::Pink()
{
}

Pink::Pink(Vec2Float pos, AttackType type,PlayerMng* mng_)
{
	unitData =
		UnitData{ L"Pink",LoadGraph(L"data/image/Hexagon_Pink.png"),1,1,
		UnitStat{ pos,1.0f,2.0f,6,10,false } };
	isSkill_ = false;
	UnitID = PlayerUnit::PINK;
	this->type = type;
	player_ = mng_;
}

Pink::~Pink()
{
}

void Pink::Init()
{
}

void Pink::Draw()
{
	Vec2Int gSize;
	GetGraphSize(unitData.imageId, &gSize.x, &gSize.y);
	DrawGraph(unitData.stat.pos.x - gSize.x / 2, unitData.stat.pos.y - gSize.y / 2, unitData.imageId, true);
}

int Pink::GetSpawnCost(void)
{
	return 10;
}

void Pink::Skill(void)
{
	player_->SetCost(player_->GetCost()+1);
}
