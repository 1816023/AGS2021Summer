#pragma once
#include "Button.h"
class RectButton :
    public Button
{
public:
    RectButton(VECTOR2 lu, VECTOR2 rd, int color, std::function<bool()> func, VECTOR2 offset);
    ~RectButton();
	void Update();
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V�����w��)
	bool IsHit(VECTOR2 mPos);
	// �{�^���̕`��
	void Draw();

private:
	//const VECTOR2 offset_;
};

