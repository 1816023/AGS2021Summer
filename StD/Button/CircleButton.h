#pragma once
#include "Button.h"
class CircleButton :
    public Button
{
public:
    CircleButton(VECTOR2 pos, int radius, int color, std::function<bool()>func, VECTOR2 offset);
    ~CircleButton();

	void Update();
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V�����w��)
	bool IsHit(VECTOR2 mPos);
	// �{�^���̕`��
	void Draw();
private:
};

