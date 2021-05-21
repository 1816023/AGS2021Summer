#pragma once
#include <functional>
#include <string>
#include "../VECTOR2.h"
enum class ButtonType
{
	Rect,
	Circle,
	RoundRect,
	BoxImage,
	CircleImage
};

class Button
{
public:
	Button(VECTOR2 offset);
	virtual ~Button();
	virtual void Update();
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V�����w��)
	virtual bool IsHit(VECTOR2 mPos)=0;
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V���������擾)
	virtual bool IsHit();
	// �����ꂽ�Ƃ��ɌĂяo��
	virtual bool PushFunction() { return func_(); }
	// ������Ă邩�̎擾
	virtual bool isPush() { return isPush_; }
	// �{�^���̕`��
	virtual void Draw()=0;
	// z���̐ݒ�
	virtual void SetZbuff(int z);
	// z���̎擾�f�t�H���g��0
	virtual int GetZBuff() { return zBuff_; }
	// �{�^����ɕ`�悷�镶���Ƃ��̈ʒu
	virtual void SetString(std::string str, VECTOR2 sPos);
protected:
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
	// Z��
	int zBuff_;

	/*--������ۊǗp--*/
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
	// �`�敶��
	std::string str_;
	// �����`��ʒu
	VECTOR2 sPos_;
	/*------------------*/
	
	// �ǂ̃^�C�v�̃{�^����
	ButtonType type_;
};

