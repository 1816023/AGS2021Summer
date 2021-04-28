#pragma once
#include <string>
#define _WtS(x) StringUtil::WStringToString(x)
#define _StW(x) StringUtil::StringToWString(x)
struct StringUtil
{
	// wstring��string�ɕϊ�����
	static std::string WStringToString(std::wstring oWString);
	// string��wstring�ɕϊ�����
	static std::wstring StringToWString(std::string oString);
};

