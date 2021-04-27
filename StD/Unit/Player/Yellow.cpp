#include <DxLib.h>
#include "../../Object/Shot/ShotMng.h"
#include "Yellow.h"

Yellow::Yellow()
{
}

Yellow::Yellow(Vec2Float pos)
{
	stat_.pos = pos;
	stat_.atkSpeed = 2;
	stat_.atkDist = 0.5f;
	stat_.power = 10;
	stat_.life = 20;
	stat_.isDead = false;
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
	lpShotMng.AddBullet(this,stat_.pos);
	lpShotMng.BulletMove(this);
}

void Yellow::Draw()
{
	lpShotMng.Draw();
	DrawCircle(stat_.pos.x, stat_.pos.y,15, 0xffff00, true);
}

Vec2Float Yellow::GetPos(void)
{
	return stat_.pos;
}

//void Yellow::Skill(void)
//{
//	stat_.life += 10;
//}
