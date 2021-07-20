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
	//// �t�H���g�ǉ�
	//static void AddStrFont(int fontSize, std::wstring name, int thick = -1);
	//// �t�H���g�擾
	//static int GetStrFont(std::wstring name);

	//static std::map<std::wstring, int>strFonts_;
};

