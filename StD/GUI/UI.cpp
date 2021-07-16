#include "UI.h"

VECTOR2 UI::GetPos()
{
	return pos_;
}

void UI::SetPos(const VECTOR2& pos)
{
	pos_ = pos;
}

VECTOR2 UI::GetSize()
{
	return size_;
}
