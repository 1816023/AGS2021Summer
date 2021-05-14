#pragma once
#include <functional>
#include <string>
#include "VECTOR2.h"
enum class ButtonType
{
	Box,
	Circle,
	RoundRect,
	BoxImage,
	CircleImage
};
class Button
{
public:
	// �P�F�̎l�p���{�^��
	Button(VECTOR2 lu,VECTOR2 rd,int color,std::function<bool()> func,VECTOR2 offset);
	// �P�F�̊ۂ��{�^��
	Button(VECTOR2 pos, int radius, int color, std::function<bool()>func, VECTOR2 offset);
	// �P�F�̊p�ۂ̃{�^��
	Button(VECTOR2 lu, VECTOR2 rd, VECTOR2 radius, int color, std::function<bool()>func, VECTOR2 offset);
	// �摜��p�����l�p���{�^��
	Button(VECTOR2 pos, VECTOR2 size, std::wstring imagePath, std::wstring pushImagePath,std::function<bool()>func , VECTOR2 offset);
	// �摜��p�����ۂ��{�^��	
	Button(VECTOR2 pos, int radius, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()>func, VECTOR2 offset);
	~Button();
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V�����w��)
	bool IsHit(VECTOR2 mPos);
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V���������擾)
	bool IsHit();
	// �����ꂽ�Ƃ��ɌĂяo��
	bool PushFunction() { return func_(); };
	// ������Ă邩�̎擾
	bool isPush() { return isPush_; }
	// �{�^���̕`��
	void Draw();
private:
	// �e�{�^�����Ƃ̓����蔻��
	bool BoxHit(VECTOR2 mPos);
	bool CircleHit(VECTOR2 mPos);
	bool RoundRectHit(VECTOR2 mPos);
	bool BoxImageHit(VECTOR2 mPos);
	bool CircleImageHit(VECTOR2 mPos);
	// �e�{�^�����Ƃ̕`��
	void BoxDraw();
	void CircleDraw();
	void RoundRect();
	void BoximageDraw();
	void CircleImageDraw();
	// ���W�␳
	const VECTOR2 offset_;
	//���݉�����Ă��邩�̃t���O
	bool isPush_;
	// �����蔻��p�̊֐��i�[�p
	std::function<bool(VECTOR2)>isHitFunc_;
	// �`��֐��i�[�p
	std::function<void()>drawFunc_;
	// 
	bool isClick_;
	/*������ۊǗp*/
	// �����ꂽ�Ƃ��ɌĂяo�����֐��i�[�p
	std::function<bool()> func_;
	// ������W
	VECTOR2 lu_;
	// �E����W
	VECTOR2 rd_;
	// �F
	int color_;
	// ���W
	VECTOR2 pos_;
	// ���a
	int radius_;
	// �p�ۗp�̔��a
	VECTOR2 radius2_;
	// �ʏ�̉摜�p�X
	std::wstring imagePath_;
	// ������Ԃ̎��̉摜�p�X
	std::wstring pushImagePath_;
	// �摜�̃T�C�Y
	VECTOR2 size_;
	// �ǂ̃^�C�v�̃{�^����
	ButtonType type_;
};

