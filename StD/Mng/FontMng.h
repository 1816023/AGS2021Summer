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
	// フォント追加※現在はサイズ指定のみ
	int AddStrFont(int fontSize, std::wstring name, int thick = -1);
	// フォント取得
	int GetStrFont(std::wstring name);
	void DeleteHandle();
private:
	FontMng() = default;
	FontMng(FontMng&) = delete;
	FontMng operator=(FontMng&) = delete;

	std::map<std::wstring, int>strFonts_;
};

