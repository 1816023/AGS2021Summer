#include <DxLib.h>
#include "Blue.h"

Blue::Blue()
{
}

Blue::Blue(Vec2Float pos)
{
	imageID = LoadGraph(L"data/image/Hexagon_Blue.png");
	stat_ = UnitStat{ pos,2,0.8f,10,20,false };
	isSkill_ = false;
}

Blue::~Blue()
{
}

void Blue::Init()
{
}

void Blue::Update(float deltaTime)
{
}

void Blue::Draw()
{
	Vec2Int gSize;
	GetGraphSize(imageID, &gSize.x, &gSize.y);
	DrawGraph(stat_.pos.x-gSize.x/2,stat_.pos.y-gSize.y/2,imageID,true);
}

//void Blue::Skill(void)
//{
//	stat_.life += 10;
//}
