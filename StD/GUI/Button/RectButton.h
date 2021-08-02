#pragma once
#include "Button.h"
class RectButton :
    public Button
{
public:
    RectButton(VECTOR2 pos, VECTOR2 size, int color, std::function<bool()> func);
    ~RectButton()override;
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V�����w��)
	bool IsHit(VECTOR2 mPos)override;
	// �{�^���̕`��
	void Draw()override;

private:
	//const VECTOR2 offset_;
};

