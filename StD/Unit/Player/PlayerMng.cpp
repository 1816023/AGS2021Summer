#include "PlayerMng.h"
#include "../../Object/Shot/ShotMng.h"
#include "../Enemy/Enemy.h"
#include "Yellow.h"
#include "Green.h"
#include "Blue.h"
#include "Pink.h"

void PlayerMng::Update(float deltaTime,std::shared_ptr<Unit> shooter)
{
    for (auto& unit : unitList_)
    {
        SkillCtl(shooter);
        unit->Update(deltaTime);
    }
}

void PlayerMng::Draw(void)
{
    for (auto& unit : unitList_)
    {
        unit->Draw();
    }
    DrawFormatString(100, 0, 0xffffff, L"cost:%d", cost);
}

bool PlayerMng::Spawner(PlayerUnit id,Vec2Float pos)
{
    std::shared_ptr<Player> ptr;
    switch (id)
    {
    case PlayerUnit::YELLOW:
        ptr = std::make_shared<Yellow>(pos,AttackType::SHOT);
        break;
    case PlayerUnit::GREEN:
        ptr = std::make_shared<Green>(pos,AttackType::AREA);
        break;
    case PlayerUnit::BLUE:
        ptr = std::make_shared<Blue>(pos, AttackType::SHOT);
        break;
    case PlayerUnit::PINK:
        ptr = std::make_shared<Pink>(pos, AttackType::SHOT,this);
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

UnitList PlayerMng::GetUnitList(void)
{
    return unitList_;
}

std::map<PlayerUnit, UnitData> PlayerMng::GetPlayerData(void)
{
    return playerData;
}

int PlayerMng::GetCost(void)
{
    return cost;
}

void PlayerMng::SetCost(int cost)
{
    this->cost = cost;
}

float PlayerMng::SpeedDelay(void)
{
    int cnt = 0;
    for (auto& unit : unitList_)
    {
        if (unit->isExecutable() && unit->GetID() == PlayerUnit::GREEN)
        {
            cnt++;
        }
    }
    auto delay = std::powf(0.3, cnt);
    return delay;
}

std::shared_ptr<Player> PlayerMng::GetUnitData(Vec2Float pos)
{
    UnitList::iterator result = unitList_.end();
    result = std::find_if(unitList_.begin(), unitList_.end(), [&](std::shared_ptr<Player> player) {return player->GetPos() == pos; });
    return (result != unitList_.end() ? (*result):nullptr);
}

PlayerMng::PlayerMng()
{
    Init();
}

void PlayerMng::SkillCtl(std::shared_ptr<Unit> shooter)
{
    auto result = std::find(unitList_.begin(), unitList_.end(), shooter);
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
            if (unit->isExecutable())
            {
                unit->Skill();
            }
        }
    }
}

PlayerMng::~PlayerMng()
{
}

void PlayerMng::Init()
{
    cost = MAX_COST;
    playerData.try_emplace(PlayerUnit::BLUE, UnitData{ L"Blue", LoadGraph(L"data/image/Hexagon_Blue.png") ,1,UnitStat{ Vec2Float(0.0f,0.0f),2,0.8f,20,20,false }});
    playerData.try_emplace(PlayerUnit::GREEN, UnitData{ L"Green", LoadGraph(L"data/image/Hexagon_Green.png"),1,UnitStat{ Vec2Float(0.0f,0.0f),2,0.8f,20,20,false }});
    playerData.try_emplace(PlayerUnit::PINK, UnitData{ L"Pink", LoadGraph(L"data/image/Hexagon_Pink.png") ,1,UnitStat{ Vec2Float(0.0f,0.0f),2,0.8f,20,20,false }});
    playerData.try_emplace(PlayerUnit::YELLOW, UnitData{ L"Yellow", LoadGraph(L"data/image/Hexagon_Yellow.png") ,1,UnitStat{ Vec2Float(0.0f,0.0f),2,0.8f,20,20,false }});
}
