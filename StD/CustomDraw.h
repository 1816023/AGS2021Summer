#pragma once
#include <string>
#include "VECTOR2.h"

#define lpCustomDraw CustomDraw::GetInstance()

class CustomDraw
{
public:
	~CustomDraw()=default;
	static CustomDraw& GetInstance()
	{
		static CustomDraw s_Instance;
		return s_Instance;
	}

	void MakeRoundRect(Vec2Float pos, Vec2Int size, Vec2Float offset, int basecolor, int alpha, bool borderline,int bordercolor=0xffffff);
	void MakeRoundButton(Vec2Float pos, Vec2Int size, Vec2Float offset, int basecolor, int shadowcolor, const TCHAR* text);
private:
	CustomDraw();

	Vec2Float pos;
};

