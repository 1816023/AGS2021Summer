#pragma once
#include "../VECTOR2.h"
#include <string>
#include <vector>

// UI�ʒuenum
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
class UI;
struct UIStat;
class Canvas
{
public:
	Canvas(VECTOR2 pos, VECTOR2 size);
	~Canvas();
	void AddUIByID(UI* ui, Justified just, int id = -1);
	void AddUIByID(UI* ui, VECTOR2& pos, int id = -1);
	void AddUIByName(UI* ui, Justified just, std::wstring name = L"");
	void AddUIByName(UI* ui, VECTOR2& pos, std::wstring name = L"");

	UI* GetUIByName(std::wstring name);
	UI* GetUIByName(int id);
	void SetColor(int color);

	void Draw();
	void Update();
private:
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
	std::vector<UIStat>UIList_;
	int color_;		// �F
};

