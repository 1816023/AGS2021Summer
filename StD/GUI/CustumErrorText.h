#pragma once
#include "../MapEnum.h"
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
	const std::vector<std::wstring>& GetErrorText();
private:
	// エラー内容
	// 最大列数（日本語全角で16文字）
	// 最大行数（6行）
	std::vector<std::wstring>errorText_;
};