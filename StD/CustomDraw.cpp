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
	Vec2Float s_pos = Vec2Float(pos.x + offset.x, pos.y + offset.y);
	Vec2Float e_pos = Vec2Float(pos.x + size.x + offset.x, pos.y + size.y + offset.y);
	drawData_.try_emplace(text, s_pos, e_pos);
	//ボタン影
	DrawRoundRect(pos.x + offset.x+7, pos.y + offset.y+5, pos.x + size.x + offset.x+7, pos.y + size.y + offset.y+5, 10, 10, shadowcolor, true);
	//ボタン
	DrawRoundRect(s_pos.x,s_pos.y,e_pos.x,e_pos.y, 10, 10, basecolor, true);
	//ボタン縁
	DrawRoundRect(pos.x + offset.x, pos.y + offset.y, pos.x + size.x + offset.x, pos.y + size.y + offset.y, 10, 10, 0xff0000, false);
	int stringWidht = GetDrawFormatStringWidth(text);
	DrawFormatString(pos.x + offset.x+(size.x/2-stringWidht/2), pos.y + offset.y, 0x000000,text);
}

std::pair<Vec2Float, Vec2Float> CustomDraw::GetDrawData(const TCHAR* keyname)
{
	return drawData_[keyname];
}

CustomDraw::CustomDraw()
{
}
