#pragma once
#include "VECTOR2.h"
struct NumberUI
{
	// wstringをstringに変換する
	static void Draw(VECTOR2 pos, VECTOR2 offset, int number);
	static void TimeDraw(VECTOR2 pos, VECTOR2 offset, int minite, int second);
};

