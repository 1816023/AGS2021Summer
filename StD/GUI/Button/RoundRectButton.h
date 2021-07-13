#pragma once
#include "Button.h"
class RoundRectButton:
	public Button
{
public:
	RoundRectButton(VECTOR2 lu, VECTOR2 size, VECTOR2 radius, int color, std::function<bool()>func, VECTOR2 offset);
	RoundRectButton(VECTOR2 size, VECTOR2 radius, int color, std::function<bool()>func, VECTOR2 offset);
	~RoundRectButton()override;
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V�����w��)
	bool IsHit(VECTOR2 mPos)override;
	// �{�^���̕`��
	void Draw()override;
private:

};

