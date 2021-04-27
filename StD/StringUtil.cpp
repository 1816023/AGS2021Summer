#include "StringUtil.h"
#include <DxLib.h>

std::string StringUtil::WStringToString(std::wstring oWString)
{
	// wstring �� SJIS
	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, (char*)NULL, 0, NULL, NULL);
	CHAR* cpMultiByte = new CHAR[iBufferSize];
	// wstring �� SJIS
	WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte, iBufferSize, NULL, NULL);
	std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);
	// �o�b�t�@�̔j��
	delete[] cpMultiByte;
	return oRet;
}
