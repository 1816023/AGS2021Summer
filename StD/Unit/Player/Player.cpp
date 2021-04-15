#include "Player.h"

void Player::Init()
{
}

void Player::Update(float deltaTime)
{
}

void Player::Draw()
{
}

bool Player::Spawner(PlayerUnit id)
{
	switch (id)
	{
    case PlayerUnit::YELLOW:
        break;
    case PlayerUnit::GREEN:
        break;
    case PlayerUnit::BLUE:
        break;
    case PlayerUnit::PINK:
        break;
    case PlayerUnit::MAX:
        break;
    default:
        return false;
        break;
	}
    return true;
}
