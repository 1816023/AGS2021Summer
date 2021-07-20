#pragma once
#include "../VECTOR2.h"
#include <string>
#include <vector>
#include <functional>

// UI����ʒuenum
enum class Justified
{
	CENTER,
	CENTER_UP,
	CENTER_DOWN,
	CENTER_LEFT,
	LEFT_UP,
	LEFT_DOWN,
	CENTER_RIGHT,
	RIGHT_UP,
	RIGHT_DOWN
};

enum class BackType
{
	Non,
	RoundRect
};

class UI;
struct UIStat;
class Canvas
{
public:
	Canvas(VECTOR2 pos, VECTOR2 size, int color = 0xffffff);
	Canvas(VECTOR2 pos, VECTOR2 size, std::wstring path);
	Canvas(VECTOR2 pos, VECTOR2 size, std::function<void(VECTOR2)> drawFunc);
	Canvas(VECTOR2 pos, VECTOR2 size, BackType back);
	~Canvas();
	// ------- UI���L�����o�X�ɒǉ����� -------
	// ID���琮��@�\���g��
	void AddUIByID(UI* ui, Justified just, int id);
	// ID���玩���ō��W�ݒ������
	void AddUIByID(UI* ui, VECTOR2 pos, int id);
	// ���O���琮��@�\���g��
	void AddUIByName(UI* ui, Justified just, std::wstring name);
	// ���O���玩���ō��W�ݒ������
	void AddUIByName(UI* ui, VECTOR2 pos, std::wstring name);
	// ----------------------------------------
	// ���O����UI���擾
	UI* GetUIByName(std::wstring name);
	// ID����UI���擾
	UI* GetUIByName(int id);
	// �L�����o�X�̐F��ݒ�
	void SetColor(int color);
	// �`��
	void Draw();
	// �X�V
	void Update();
	// ����UI����������
	void ClearUI();
	// �A�N�e�B�u�ɂ��邩�ǂ���
	void SetActive(bool active);
private:
	// ������
	void Init();
	// �L�����o�X�w�i�`��
	void BackDraw();
	// UI�ʒu�̍��W��Ԃ�
	VECTOR2 PosToJustified(const Justified& just, const VECTOR2& size);


	// -- UI�̃T�C�Y��n���Ɗe���ё����̍��W��Ԃ��֐�	--
	VECTOR2 Center(const VECTOR2& size);
	VECTOR2 Left(const VECTOR2& size);
	VECTOR2 Right(const VECTOR2& size);
	VECTOR2 Up(const VECTOR2& size);
	VECTOR2 Down(const VECTOR2& size);
	// ---------------------------------------------------

	VECTOR2 pos_;	// ������W
	VECTOR2 size_;	// �傫��
	std::vector<UIStat>UIList_;	// UI�̃��X�g
	int color_;		// �F
	int gHandle_;	// �摜�n���h��
	BackType backT_;	// �w�i�̃^�C�v
	bool isActive_;
	std::function<void(VECTOR2)> drawFunc_;	// �`��function #VECTOR2��offset
};

