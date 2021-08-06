#pragma once
#include "UI.h"

class Box : public UI
{
public:
	// ��(�F�Ɠh��Ԃ�������)
	Box(VECTOR2 pos, VECTOR2 size, int color, bool fillF);
	// ��(�h��Ԃ��̐F��C�ӂŐݒ肷��)
	Box(VECTOR2 pos, VECTOR2 size, int outColor,int inColor);

	// �X�V
	bool Update();
	// �`��
	void Draw();
private:
	int outColor_;	// �O�g�F(�P�F�̏ꍇ���̐F�����f�����)
	int inColor_;	// ���g�F
	bool fillF_;	// �����𓧉߂��邩�ǂ���
};

