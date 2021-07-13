#include <DxLib.h>
#include "CustomDraw.h"

void CustomDraw::MakeRoundRect(Vec2Float pos, Vec2Int size, Vec2Float offset, int basecolor, int alpha, bool borderline, int bordercolor)
{
	this->pos = pos + offset;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRoundRect(this->pos.x, this->pos.y, this->pos.x + size.x, this->pos.y + size.y, 10, 10, basecolor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	if (borderline)
	{
		DrawRoundRect(this->pos.x, this->pos.y, this->pos.x + size.x, this->pos.y + size.y, 10, 10, bordercolor, false);
	}
}

void CustomDraw::MakeRoundButton(Vec2Float pos, Vec2Int size, Vec2Float offset, int basecolor, int shadowcolor,const TCHAR* text)
{
	//ボタン
	DrawRoundRect(pos.x + offset.x, pos.y + offset.y, pos.x + size.x + offset.x, pos.y + size.y +offset.y, 10, 10, basecolor, true);
	//ボタン縁
	//DrawRoundRect(pos.x + size.x + 5, pos.y + size.y - 20, pos.x + size.x + 95, pos.y + size.y - 50, 10, 10, 0xffffff, true);
	//ボタン影
	//DrawRoundRect(pos.x + size.x + 5, pos.y + size.y - 20, pos.x + size.x + 95, pos.y + size.y - 50, 10, 10, shadowcolor, false);
	DrawFormatString(pos.x + size.x + 15, size.y - 45, 0xffffff,text);
}

CustomDraw::CustomDraw()
{
}
