#include "Player.h"
#include "PlayerMng.h"

void Player::Init()
{
}

void Player::Update(float deltaTime)
{
	if (!executable)
	{
		coolTime_--;
	}
	else
	{
		coolTime_++;
	}
}

void Player::Draw()
{
}

void Player::LevelShift(int num)
{
	unitData.lv += num;
	auto mag = 1.0 + (0.1 * num);
	unitData.stat.power = (unitData.stat.power * mag) + 0.5;
}

void Player::SetExecutable(bool flag)
{
	executable = flag;
}

void Player::SetPosition(Vec2Float pos)
{
	unitData.stat.pos = pos;
}

void Player::SetHP(int power)
{
	unitData.stat.power = power;
}
