#pragma once
#include <DxLib.h>
#include "../VECTOR2.h"

typedef enum
{
	INTERFERENCE,	// 妨害
	SLIP_DAMAGE,	// 継続ダメージ
	SUPPORT,		// 支援
	EXPLOSION,		// 単発ダメージ
	MAX
}TRAP_ID;

class TrapManager
{
public:
	TrapManager();
	virtual ~TrapManager();
private:
	virtual void Draw();
protected:
	VECTOR2 pos;
	int cnt;
	int image[TRAP_ID::MAX];
};