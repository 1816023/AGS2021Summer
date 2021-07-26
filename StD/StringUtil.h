#pragma once
#include <string>
#include <map>
#define _WtS(x) StringUtil::WStringToString(x)
#define _StW(x) StringUtil::StringToWString(x)
struct StringUtil
{
public:
	// wstring��string�ɕϊ�����
	static std::string WStringToString(std::wstring oWString);
	// string��wstring�ɕϊ�����
	static std::wstring StringToWString(std::string oString);
	// �g���q�폜
	static std::string SpritExtention(std::string string);
};

