#include "CustumErrorText.h"
#include <DxLib.h>
#include "StringUtil.h"

CustumErrorText::CustumErrorText()
{
}

CustumErrorText::~CustumErrorText()
{
}

void CustumErrorText::ResetErrorTexts()
{
	errorText_.clear();
}

void CustumErrorText::AddErrorText(std::string text)
{
	errorText_.push_back(StringUtil::StringToWString(text));
}

void CustumErrorText::AddErrorText(std::wstring text)
{
	errorText_.push_back(text);
}

void CustumErrorText::DrawErrorText(int x, int y, int errorCode, int color)
{
	DrawString(x, y, errorText_[errorCode].c_str(), color);
}
