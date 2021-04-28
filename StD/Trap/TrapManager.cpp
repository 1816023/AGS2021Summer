#include "TrapManager.h"

TrapManager::TrapManager()
{
	image[TRAP_ID::INTERFERENCE] = LoadGraph(L"data/image/interference.png");
	image[TRAP_ID::SLIP_DAMAGE] = LoadGraph(L"data/image/slip_damege.png");
	image[TRAP_ID::SUPPORT] = LoadGraph(L"data/image/support.png");
	image[TRAP_ID::EXPLOSION] = LoadGraph(L"data/image/explosion.png");
}

TrapManager::~TrapManager()
{
}

void TrapManager::Draw()
{
}
