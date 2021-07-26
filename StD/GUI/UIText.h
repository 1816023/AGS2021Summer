#pragma once
#include "UI.h"
#include <string>
class UIText : public UI
{
public:
	UIText(VECTOR2 pos, std::wstring str);
	UIText(VECTOR2 pos, std::wstring str, int fontSize);
	~UIText() = default;
	bool Update();
	// �{�^���̕`��
	void Draw();
private:
	std::wstring str_;
	int fontHandle_;
};

