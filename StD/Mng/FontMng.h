#pragma once
#include <string>
#include <map>
#define lpFontMng FontMng::Instance()

class FontMng
{
public:
	static FontMng& Instance()
	{
		static FontMng font;
		return font;
	}
	// �t�H���g�ǉ������݂̓T�C�Y�w��̂�
	int AddStrFont(int fontSize, std::wstring name, int thick = -1);
	// �t�H���g�擾
	int GetStrFont(std::wstring name);
	void DeleteHandle();
private:
	FontMng() = default;
	FontMng(FontMng&) = delete;
	FontMng operator=(FontMng&) = delete;

	std::map<std::wstring, int>strFonts_;
};

