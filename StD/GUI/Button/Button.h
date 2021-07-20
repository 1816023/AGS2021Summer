#pragma once
#include <functional>
#include <string>
#include "../../VECTOR2.h"
#include "../UI.h"
enum class ButtonType
{
	Rect,
	Circle,
	RoundRect,
	BoxImage,
	CircleImage
};

class Button : public UI
{
public:
	Button(VECTOR2 offset);
	virtual ~Button();
	virtual bool Update();
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V�����w��)
	virtual bool IsHit(VECTOR2 mPos)=0;
	// �J�[�\��������ʒu�Ƃ̓����蔻��(�}�E�X�|�W�V���������擾)
	const bool IsHit();
	// �����ꂽ�Ƃ��ɌĂяo��
	const bool PushFunction() const { return func_(); }
	// ������Ă邩�̎擾
	const bool IsPush() const { return isPush_; }
	// �{�^���̕`��
	virtual void Draw()=0;
	// z���̐ݒ�
	void SetZbuff(int z);
	// z���̎擾�f�t�H���g��0
	const int GetZBuff() const { return zBuff_; }
	// �{�^����ɕ`�悷�镶���Ƃ��̈ʒu
	void SetString(std::string str, VECTOR2 sPos, int fontHandle=-1);
	// �A�b�v�f�[�g�Ŏ����œ����蔻��┻�菈�����s���悤�ɂȂ�
	void SetAuto();
	// �N���b�N�ŉ����ꂽ���łȂ����ꂽ�Ƃ��ɏ������s���悤�ɂȂ�
	void SetReversePush();
	// DXLIB��MOUSE_INPUT_LEFT,MOUSE_INPUT_RIGHT,MOUSE_INPUT_WHEEL�̂����ꂩ���w�肷��
	void SetClickType(int type);
	// �����p�̃^�O�ݒ�
	void SetTag(int tag);
	// �����p�^�O�擾
	const int GetTag() { return tag_; }
	// �������Ƃ��̃T�E���h�n���h���ݒ�
	// -2,�w��Ȃ��Ńf�t�H���g��SE��ݒ�
	void SetSound(int handle=-2);
	// str�̎擾
	const std::string GetStr()const { return str_; }
	// �g��k���X�P�[���̐ݒ�
	void SetScale(float scale);
	// �t�H���g��ݒ肷��
	void SetFont(int handle);
protected:
	// ���W�␳
	const VECTOR2 offset_;
	//���݉�����Ă��邩�̃t���O
	bool isPush_;
	// �����蔻��p�̊֐��i�[�p
	std::function<bool(VECTOR2)>isHitFunc_;
	// �`��֐��i�[�p
	std::function<void()>drawFunc_;
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
	// �{�^�����������Ƃ��̃T�E���h�n���h���i�[�p
	int soundHandle_;
	// �g��k���X�P�[���l
	float scale_;


	/*--������ۊǗp--*/
	// �����ꂽ�Ƃ��ɌĂяo�����֐��i�[�p
	std::function<bool()> func_;
	// ������W
	VECTOR2 lu_;
	// �E����W
	VECTOR2 rd_;
	// �F
	int color_;
	//// ���W
	//VECTOR2 pos_;
	// ���a
	int radius_;
	// �p�ۗp�̔��a
	VECTOR2 radius2_;
	// �ʏ�̉摜�p�X
	std::wstring imagePath_;
	// ������Ԃ̎��̉摜�p�X
	std::wstring pushImagePath_;
	//// �摜�̃T�C�Y
	//VECTOR2 size_;
	// �`�敶��
	std::string str_;
	// �����`��ʒu
	VECTOR2 sPos_;
	/*------------------*/
	
};

