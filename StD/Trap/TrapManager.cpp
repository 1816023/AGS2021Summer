#include "TrapManager.h"
#include "Explosion.h"
#include "Interference.h"
#include "SlipDamage.h"
#include "Support.h"

bool TrapManager::Spawner(TRAP_ID id, Vec2Float pos)
{
	std::shared_ptr<Trap> ptr;
    switch (id)
    {
    case TRAP_ID::INTERFERENCE:
        ptr = std::make_shared<Interference>(pos);
        break;
    case TRAP_ID::SLIP_DAMAGE:
        ptr = std::make_shared<SlipDamage>(pos);
        break;
    case TRAP_ID::SUPPORT:
        ptr = std::make_shared<Support>(pos);
        break;
    case TRAP_ID::EXPLOSION:
        ptr = std::make_shared<Explosion>(pos);
        break;
    case TRAP_ID::MAX:
        break;
    default:
        return false;
        break;
    }
    trapList.emplace_back(ptr);
	return false;
}

float TrapManager::Efficacy(float num, bool flag)
{
    for (auto& trap : trapList)
    {
        return trap->Efficacy(num, flag);
    }
}

TrapManager::TrapManager()
{
}

TrapManager::~TrapManager()
{
}

void TrapManager::Draw()
{
    for (auto& trap : trapList)
    {
        trap->Draw();
    }
}

void TrapManager::Delete()
{
    trapList.clear();
}

int TrapManager::TrapCost(int cost)
{
    for (auto& trap : trapList)
    {
        return trap->TrapCost(cost);
    }
}
