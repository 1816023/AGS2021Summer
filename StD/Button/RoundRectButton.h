#pragma once
#include "Button.h"
class RoundRectButton:
	public Button
{
public:
	RoundRectButton(VECTOR2 lu, VECTOR2 rd, VECTOR2 radius, int color, std::function<bool()>func, VECTOR2 offset);
	~RoundRectButton();
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V�����w��)
	bool IsHit(VECTOR2 mPos);
	// �{�^���̕`��
	void Draw();
private:

};

