#include <DxLib.h>
#include "Yellow.h"

Yellow::Yellow()
{
}

Yellow::Yellow(Vec2Float pos)
{
	imageID = LoadGraph(L"data/image/Hexagon_Yellow.png");
	state_ = UnitStat{ pos,2,0.8f,10,20,false };
	isSkill_ = false;
}

Yellow::~Yellow()
{
}

void Yellow::Init()
{
}

void Yellow::Update(float deltaTime)
{
}

void Yellow::Draw()
{
	Vec2Int gSize;
	GetGraphSize(imageID, &gSize.x, &gSize.y);
	DrawGraph(state_.pos.x-gSize.x/2, state_.pos.y-gSize.y/2,imageID,true);
}

int Yellow::GetSpawnCost(void)
{
	return 5;
}

//void Yellow::Skill(void)
//{
//	state_.life += 10;
//}
