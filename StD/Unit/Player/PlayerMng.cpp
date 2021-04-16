#include "PlayerMng.h"
#include "../../Object/Shot/ShotMng.h"
#include "Yellow.h"

void PlayerMng::Updata(float deltaTime)
{
    for (auto& unit:unitList_)
    {
        lpShotMng.AddBullet(unit);
    }
}

bool PlayerMng::Spawner(PlayerUnit id)
{
    std::shared_ptr<Player> ptr;
    switch (id)
    {
    case PlayerUnit::YELLOW:
        ptr = std::make_shared<Yellow>();
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
