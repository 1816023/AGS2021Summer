#pragma once

enum class TRAP_ID
{
	INTERFERENCE,	// 妨害
	SLIP_DAMEGE,	// 継続ダメージ
	SUPPORT,		// 支援
	EXPLOSION,		// 単発ダメージ
	MAX
};

class TrapManager
{
public:
	TrapManager();
	virtual ~TrapManager();

private:
};

