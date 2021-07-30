#pragma once
#include <DxLib.h>
#include "Trap.h"
#include "../VECTOR2.h"
#include <vector>
#include <memory>

#define lpTrapManager TrapManager::GetInstance()

enum class TRAP_ID
{
	INTERFERENCE,	// 移動妨害
	SLIP_DAMAGE,	// 継続ダメージ
	SUPPORT,		// 支援
	EXPLOSION,		// 単発ダメージ
	DEFENSE_DOWN,	// 防御ダウン
	POWER_DOWN,		// 攻撃ダウン
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
	float Update(float num);
	void Draw();
	void Delete();
	int TrapCost(int cost);

private:
	TrapManager();
	~TrapManager();
	std::vector<std::shared_ptr<Trap>> trapList;
};