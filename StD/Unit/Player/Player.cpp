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

void Player::SetExecutable(bool flag)
{
	executable = flag;
}
