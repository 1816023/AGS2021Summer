#include "PlayerMng.h"
#include "../../Object/Shot/ShotMng.h"
#include "Yellow.h"
#include "Green.h"
#include "Blue.h"
#include "Pink.h"

void PlayerMng::Update(float deltaTime)
{
}

void PlayerMng::Update(float deltaTime,Vec2Float pos)
{
    for (auto& unit : unitList_)
    {
        //unit->Update(deltaTime);
        lpShotMng.AddBullet(unit,unit->GetPos());
        lpShotMng.BulletMove(unit,pos);
    }
    SkillCtl();
}

void PlayerMng::Draw(void)
{
    for (auto& unit : unitList_)
    {
        unit->Draw();
    }
    lpShotMng.Draw();
    DrawFormatString(100, 0, 0xffffff, L"cost:%d", cost);
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
    auto spawnCost = ptr->GetSpawnCost();
    if ((cost - spawnCost) >= 0)
    {
        cost -= spawnCost;
        unitList_.emplace_back(ptr);
    }
    return true;
}

int PlayerMng::GetCost(void)
{
    return cost;
}

void PlayerMng::SetCost(int cost)
{
    this->cost = cost;
}

PlayerMng::PlayerMng()
{
}

void PlayerMng::SkillCtl(void)
{
    auto result = std::find(unitList_.begin(), unitList_.end(), lpShotMng.GetShooterPtr());
    if (result != unitList_.end())
    {
        if ((*result)->GetID() == PlayerUnit::PINK)
        {
            (*result)->Skill();
        }
    }
    for (auto& unit : unitList_)
    {
        if (unit->GetID() != PlayerUnit::PINK)
        {
            unit->Skill();
        }
    }
}

void PlayerMng::Init()
{
    cost = MAX_COST;
}
