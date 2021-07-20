#pragma once
#include <string>
#include <map>
#define _WtS(x) StringUtil::WStringToString(x)
#define _StW(x) StringUtil::StringToWString(x)

struct StringUtil
{
public:
	// wstringをstringに変換する
	static std::string WStringToString(std::wstring oWString);
	// stringをwstringに変換する
	static std::wstring StringToWString(std::string oString);
	// 拡張子削除
	static std::string SpritExtention(std::string string);
	//// フォント追加
	//static void AddStrFont(int fontSize, std::wstring name, int thick = -1);
	//// フォント取得
	//static int GetStrFont(std::wstring name);

	//static std::map<std::wstring, int>strFonts_;
};

