#include <DxLib.h>
#include "Green.h"

Green::Green()
{
}

Green::Green(Vec2Float pos)
{
	imageID = LoadGraph(L"data/image/Hexagon_Green.png");
	stat_ = UnitStat{ pos,15.0f,2.0f,6,10,false };
	isSkill_ = false;
}

Green::~Green()
{
}

void Green::Init()
{
}

void Green::Update(float deltaTime)
{
}

void Green::Draw()
{
	Vec2Int gSize;
	GetGraphSize(imageID, &gSize.x, &gSize.y);
	DrawGraph(stat_.pos.x-gSize.x/2,stat_.pos.y-gSize.y/2,imageID,true);
}

//void Green::Skill(void)
//{
//	stat_.life += 10;
//}
