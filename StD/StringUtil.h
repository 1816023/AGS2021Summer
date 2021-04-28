#pragma once
#include <string>
#define _WtS(x) StringUtil::WStringToString(x)
#define _StW(x) StringUtil::StringToWString(x)
struct StringUtil
{
	// wstring‚ðstring‚É•ÏŠ·‚·‚é
	static std::string WStringToString(std::wstring oWString);
	// string‚ðwstring‚É•ÏŠ·‚·‚é
	static std::wstring StringToWString(std::string oString);
};

