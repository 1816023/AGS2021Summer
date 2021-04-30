#pragma once
#include <DxLib.h>
#include "../VECTOR2.h"

typedef enum
{
	INTERFERENCE,	// �W�Q
	SLIP_DAMAGE,	// �p���_���[�W
	SUPPORT,		// �x��
	EXPLOSION,		// �P���_���[�W
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