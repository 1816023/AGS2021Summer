#pragma once
#include "UI.h"
#include <string>
class UIText : public UI
{
public:
	UIText(VECTOR2 pos, std::wstring str, int fontSize = 10);
	~UIText() = default;
	bool Update();
	// ƒ{ƒ^ƒ“‚Ì•`‰æ
	void Draw();
private:
	std::wstring str_;
};

