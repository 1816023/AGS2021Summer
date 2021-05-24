#pragma once
#include "Button.h"
class ImageCircleButton :
    public Button
{
public:
    ImageCircleButton(VECTOR2 pos, int radius, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()>func, VECTOR2 offset);
    ~ImageCircleButton();
	void Update();
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V�����w��)
	bool IsHit(VECTOR2 mPos);
	// �{�^���̕`��
	void Draw();
private:
};

