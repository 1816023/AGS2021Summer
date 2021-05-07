#include "Unit.h"

float Unit::GetBulletSpeed(void)
{
	return state_.atkSpeed;
}

float Unit::GetAtkRange(void)
{
	return state_.atkRange;
}

const Vec2Float Unit::GetPos()
{
	return state_.pos;
}

void Unit::SetPosition(Vec2Float pos)
{
	state_.pos = pos;
}

unsigned int Unit::GetHP()
{
	return state_.life;
}

const bool Unit::IsDeath()
{
	return state_.isDead;
}
