#pragma once
#include <DxLib.h>

enum class TRAP_ID
{
	INTERFERENCE,	// �W�Q
	SLIP_DAMAGE,	// �p���_���[�W
	SUPPORT,		// �x��
	EXPLOSION,		// �P���_���[�W
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
	int slipDamage;	// �p���_���[�W�p�`��ϐ�
};