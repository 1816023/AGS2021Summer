#pragma once
#include <DxLib.h>
#include "Trap.h"
#include "../VECTOR2.h"
#include <vector>
#include <memory>

#define lpTrapManager TrapManager::GetInstance()

enum class TRAP_ID
{
	INTERFERENCE,	// 妨害
	SLIP_DAMAGE,	// 継続ダメージ
	SUPPORT,		// 支援
	EXPLOSION,		// 単発ダメージ
	MAX
};

class TrapManager
{
public:
	static TrapManager& GetInstance()
	{
		static TrapManager s_Instance;
		return s_Instance;
	}
	bool Spawner(TRAP_ID id, Vec2Float pos);
	void Draw();

private:
	TrapManager();
	~TrapManager();
	std::vector<std::shared_ptr<Trap>> trapList;
};