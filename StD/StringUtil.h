#pragma once
#include <string>
#define _WtS(x) StringUtil::WStringToString(x)
#define _StW(x) StringUtil::StringToWString(x)
struct StringUtil
{
	// wstring‚ğstring‚É•ÏŠ·‚·‚é
	static std::string WStringToString(std::wstring oWString);
	// string‚ğwstring‚É•ÏŠ·‚·‚é
	static std::wstring StringToWString(std::string oString);
	// Šg’£qíœ
	static std::string SpritExtention(std::string string);
};

