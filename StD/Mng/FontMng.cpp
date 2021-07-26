#include "FontMng.h"
#include <DxLib.h>

int FontMng::AddStrFont(int fontSize, std::wstring name, int thick)
{
	if (strFonts_.find(name) == strFonts_.end())
	{
		int handle = CreateFontToHandle(name.c_str(), fontSize, thick);
		strFonts_.emplace(name, handle);
	}
	return strFonts_[name];
}

int FontMng::GetStrFont(std::wstring name)
{
	return strFonts_[name];
}
