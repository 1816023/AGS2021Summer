#pragma once
#include "Button.h"
class ImageRectButton :
    public Button
{
public:
    ImageRectButton(VECTOR2 pos, VECTOR2 size, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()>func, VECTOR2 offset);
    ~ImageRectButton();
	void Update();
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V�����w��)
	bool IsHit(VECTOR2 mPos);
	// �{�^���̕`��
	void Draw();
private:
};

