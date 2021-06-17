#pragma once
#include <string>
#define _WtS(x) StringUtil::WStringToString(x)
#define _StW(x) StringUtil::StringToWString(x)
struct StringUtil
{
	// wstringをstringに変換する
	static std::string WStringToString(std::wstring oWString);
	// stringをwstringに変換する
	static std::wstring StringToWString(std::string oString);
	// 拡張子削除
	static std::string SpritExtention(std::string string);
};

