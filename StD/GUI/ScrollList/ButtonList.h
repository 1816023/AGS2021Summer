#pragma once
#include "ScrollList.h"
#include "../Button/RectButton.h"
class ButtonList :
	public ScrollList
{
public:
	ButtonList(VECTOR2 pos, VECTOR2 size);
	~ButtonList();
	bool Add(int color, std::function<bool()> func);
	bool Del();
	void Update();
	void Draw();
	int GetSize() { return list_.size(); }
private:
	std::list<std::unique_ptr<RectButton>>list_;
};

