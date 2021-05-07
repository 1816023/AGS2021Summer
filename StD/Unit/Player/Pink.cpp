#include <DxLib.h>
#include "Pink.h"

Pink::Pink()
{
}

Pink::Pink(Vec2Float pos)
{
	imageID = LoadGraph(L"data/image/Hexagon_Pink.png");
	stat_ = UnitStat{ pos,1.0f,2.0f,6,10,false };
	isSkill_ = false;
}

Pink::~Pink()
{
}

void Pink::Init()
{
}

void Pink::Update(float deltaTime)
{
}

void Pink::Draw()
{
	Vec2Int gSize;
	GetGraphSize(imageID, &gSize.x, &gSize.y);
	DrawGraph(stat_.pos.x-gSize.x/2,stat_.pos.y-gSize.y/2,imageID,true);
}

//void Pink::Skill(void)
//{
//	stat_.life += 10;
//}
