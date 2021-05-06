#pragma once
#include <memory>
#include <array>
#include"VECTOR2.h"

#define lpMouseController MouseController::GetInstance()

class MouseController
{
public:
	static MouseController& GetInstance()
	{
		return (*s_Instans);
	}

	bool GetClickTrg(int mouseType);		// �N���b�N�����u�Ԃ̏ꍇ�Atrue
	bool GetClicking(int mouseType);		// �N���b�N���̏ꍇ�Atrue
	bool GetClickUp(int mouseType);			// �N���b�N����߂��ꍇ�Atrue
	void Update(void);		// �}�E�X�̏�ԍX�V
	const VECTOR2& GetPos() { return pos; }	// �}�E�X�̈ʒu�̎擾
	const int& GetWheel() { return wheel; }	// �z�C�[���̎擾
	const bool IsHitBoxToMouse(VECTOR2 lu, VECTOR2 rd);
private:
	struct MouseDelete
	{
		void operator()(MouseController* mouseController) const
		{
			delete mouseController;
		}
	};
	MouseController();
	~MouseController();

	VECTOR2 pos;	// �}�E�X�̍��W
	char data;		// ���݂̃}�E�X�̃N���b�N���
	char dataOld;	// 1�t���[���O�̃}�E�X�̃N���b�N���
	int wheel;		// �z�C�[�������l

	static std::unique_ptr<MouseController, MouseDelete> s_Instans;
};

