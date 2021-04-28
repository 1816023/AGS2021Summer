#include <DxLib.h>
#include "Yellow.h"

Yellow::Yellow()
{
}

Yellow::Yellow(Vec2Float pos)
{
	imageID = LoadGraph(L"data/image/Hexagon_Yellow.png");
	stat_ = UnitStat{ pos,2,0.8f,10,20,false };
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
	DrawGraph(stat_.pos.x-gSize.x/2,stat_.pos.y-gSize.y/2,imageID,true);
}

Vec2Float Yellow::GetPos(void)
{
	return stat_.pos;
}

float Yellow::GetBulletSpeed(void)
{
	return stat_.atkSpeed;
}

float Yellow::GetAtkRange(void)
{
	return stat_.atkDist;
}

//void Yellow::Skill(void)
//{
//	stat_.life += 10;
//}
