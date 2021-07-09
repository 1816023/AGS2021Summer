#include <DxLib.h>
#include "PlayerMng.h"
#include "Pink.h"

Pink::Pink()
{
}

Pink::Pink(Vec2Float pos, AttackType type,PlayerMng* mng_)
{
	imageID = LoadGraph(L"data/image/Hexagon_Pink.png");
	state_ = UnitStat{ pos,1.0f,2.0f,6,10,false };
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
	GetGraphSize(imageID, &gSize.x, &gSize.y);
	DrawGraph(state_.pos.x-gSize.x/2, state_.pos.y-gSize.y/2,imageID,true);
}

int Pink::GetSpawnCost(void)
{
	return 10;
}

void Pink::Skill(void)
{
	player_->SetCost(player_->GetCost()+1);
}
