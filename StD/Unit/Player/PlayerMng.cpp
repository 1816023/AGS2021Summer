#include "PlayerMng.h"
#include "../../Object/Shot/ShotMng.h"
#include "Yellow.h"
#include "Green.h"
#include "Blue.h"
#include "Pink.h"

void PlayerMng::Update(float deltaTime)
{
    for (auto& unit : unitList_)
    {
        unit->Update(deltaTime);
        lpShotMng.AddBullet(unit,unit->GetPos());
        lpShotMng.BulletMove(unit);
    }
}

void PlayerMng::Draw(void)
{
    for (auto& unit : unitList_)
    {
        unit->Draw();
    }
    lpShotMng.Draw();
}

bool PlayerMng::Spawner(PlayerUnit id,Vec2Float pos)
{
    std::shared_ptr<Player> ptr;
    switch (id)
    {
    case PlayerUnit::YELLOW:
        ptr = std::make_shared<Yellow>(pos);
        break;
    case PlayerUnit::GREEN:
        ptr = std::make_shared<Green>(pos);
        break;
    case PlayerUnit::BLUE:
        ptr = std::make_shared<Blue>(pos);
        break;
    case PlayerUnit::PINK:
        ptr = std::make_shared<Pink>(pos);
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

Vec2Float PlayerMng::GetPos(void)
{
    return Vec2Float();
}

PlayerMng::PlayerMng()
{
}

void PlayerMng::Init()
{
}
