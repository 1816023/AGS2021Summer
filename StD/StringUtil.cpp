#include "StringUtil.h"
#include <DxLib.h>

std::map<std::wstring, int> StringUtil::strFonts_ = {};


std::string StringUtil::WStringToString(std::wstring oWString)
{
	// wstring → SJIS
	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, (char*)NULL, 0, NULL, NULL);
	CHAR* cpMultiByte = new CHAR[iBufferSize];
	// wstring → SJIS
	WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte, iBufferSize, NULL, NULL);
	std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);
	// バッファの破棄
	delete[] cpMultiByte;
	return oRet;
}

std::wstring StringUtil::StringToWString(std::string oString)
{  
    // SJIS → wstring
    int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, (wchar_t*)NULL, 0);
    wchar_t* cpUCS2 = new wchar_t[iBufferSize];
    // SJIS → wstring
    MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2, iBufferSize);
    // stringの生成
    std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);
    // バッファの破棄
    delete[] cpUCS2;
    return oRet;
}

std::string StringUtil::SpritExtention(std::string string)
{
	int idx = static_cast<int>(string.rfind("."));
	if (idx == std::string::npos)
	{
		return string;
	}
	return string.substr(0, idx);
}

void StringUtil::AddStrFont(int fontSize, std::wstring name, int thick)
{
	int handle = CreateFontToHandle(name.c_str(), fontSize, thick);
	strFonts_.try_emplace(name, handle);
}

int StringUtil::GetStrFont(std::wstring name)
{
	return strFonts_[name];
}
