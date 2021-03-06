#include "Unit.h"

const float Unit::GetAttackSpan(void)
{
	return state_.atkSpeed;
}

const float Unit::GetAtkRange(void)
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

const int Unit::GetHP()
{
	return state_.life;
}

void Unit::SetHP(int power)
{
	state_.life -= std::abs(power);
	if (state_.life <= 0)
	{
		state_.isDead = true;
	}
}

unsigned int Unit::GetAttackPower(void)
{
	return state_.power;
}

//void Unit::SetDeath(bool flag)
//{
//	state_.isDead = flag;
//}

const bool Unit::IsDeath()
{
	return state_.isDead;
}
