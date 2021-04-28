#include "Unit.h"

const Vec2Float Unit::GetPosition()
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
