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
	virtual bool Update();
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V�����w��)
	virtual bool IsHit(VECTOR2 mPos)=0;
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V���������擾)
	virtual const bool IsHit();
	// �����ꂽ�Ƃ��ɌĂяo��
	virtual const bool PushFunction() const { return func_(); }
	// ������Ă邩�̎擾
	virtual const bool isPush() const { return isPush_; }
	// �{�^���̕`��
	virtual void Draw()=0;
	// z���̐ݒ�
	virtual void SetZbuff(int z);
	// z���̎擾�f�t�H���g��0
	virtual const int GetZBuff() const { return zBuff_; }
	// �{�^����ɕ`�悷�镶���Ƃ��̈ʒu
	virtual void SetString(std::string str, VECTOR2 sPos, int fontHandle=-1);
	// �A�b�v�f�[�g�Ŏ����œ����蔻��┻�菈�����s���悤�ɂȂ�
	virtual void SetAuto();
	// �N���b�N�ŉ����ꂽ���łȂ����ꂽ�Ƃ��ɏ������s���悤�ɂȂ�
	virtual void SetReversePush();
	// DXLIB��MOUSE_INPUT_LEFT,MOUSE_INPUT_RIGHT,MOUSE_INPUT_WHEEL�̂����ꂩ���w�肷��
	virtual void SetClickType(int type);
	// �����p�̃^�O�ݒ�
	virtual void SetTag(int tag);
	virtual const int GetTag() { return tag_; }
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
	// ���������̃t���O
	bool autoFlag_;
	// ���ꂽ�Ƃ��ɏ��������邩�̃t���O
	bool reverseFlag_;
	// �ǂ̃^�C�v�̃{�^����
	ButtonType type_;
	// DxLib�̃}�E�X�N���b�N�̔���łǂ̔�����g�p���邩
	// �f�t�H���g��MOUSE_INPUT_LEFT
	int clickType_;
	// �t�H���g�n���h��
	int fontHandle_;
	// �����p�^�O
	int tag_;
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
	
};

