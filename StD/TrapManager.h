#pragma once

enum class TRAP_ID
{
	INTERFERENCE,	// �W�Q
	SLIP_DAMEGE,	// �p���_���[�W
	SUPPORT,		// �x��
	EXPLOSION,		// �P���_���[�W
	MAX
};

class TrapManager
{
public:
	TrapManager();
	virtual ~TrapManager();

private:
};

