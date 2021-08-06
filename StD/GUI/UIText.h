#pragma once
#include "UI.h"
#include <string>
class UIText : public UI
{
public:
	UIText(VECTOR2 pos, std::wstring str, int color = 0xffffff);
	UIText(VECTOR2 pos, std::wstring str, int fontSize, std::wstring name, int color);
	UIText(VECTOR2 pos, std::wstring str, int fontHandle, int color);
	~UIText() = default;
	bool Update();
	// Text‚Ì•`‰æ
	void Draw();
	void SetText(std::wstring str);
	void SetColor(int color);

private:
	std::wstring str_;
	int fontHandle_;
	int color_;
};

