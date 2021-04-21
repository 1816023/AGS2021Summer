#pragma once
#include <DxLib.h>

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
	TrapManager();
	virtual ~TrapManager();

	virtual void Update();

private:
	virtual void Draw();
protected:
	int slipDamage;	// 継続ダメージ用描画変数
};