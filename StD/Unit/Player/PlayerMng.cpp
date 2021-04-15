#include "PlayerMng.h"
#include "Yellow.h"

bool PlayerMng::Spawner(PlayerUnit id)
{
    std::unique_ptr<Player> ptr;
    switch (id)
    {
    case PlayerUnit::YELLOW:
        ptr = std::make_unique<Yellow>();
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
    unitList_.emplace_back(ptr);
    return true;
}

PlayerMng::PlayerMng()
{
}

void PlayerMng::Init()
{
}
