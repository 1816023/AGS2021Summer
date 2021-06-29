#pragma once
#include "MapEnum.h"
#include <string>
#include <vector>
class CustumErrorText
{
public:
	CustumErrorText();
	~CustumErrorText();
	void ResetErrorTexts();
	void AddErrorText(std::string text);
	void AddErrorText(std::wstring text);
	void DrawErrorText(int x, int y, int errorCode, int color = 0xffffff);
private:
	// �G���[���e
	// �ő�񐔁i���{��S�p��16�����j
	// �ő�s���i6�s�j
	std::vector<std::wstring>errorText_;
};