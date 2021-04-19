#include "Yellow.h"

Yellow::Yellow()
{
	Init();
}

Yellow::~Yellow()
{
}

void Yellow::Init()
{
	stat_.pos = Vec2Float(100.0f, 100.0f);
	stat_.atkSpeed = 2;
	stat_.atkDist = 0.5f;
	stat_.power = 10;
	stat_.life = 20;
	stat_.isDead = false;
	isSkill_ = false;
}

void Yellow::Update()
{
}

void Yellow::Draw()
{
}

void Yellow::Skill(void)
{
	stat_.life += 10;
}
