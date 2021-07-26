#pragma once
#ifdef _DEBUG
#define AST(){\
	TCHAR ast_mes[256];\
	wsprintf(ast_mes, L"%s %d行目￥0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, L"ｱｻｰﾄ表示", MB_OK);\
	}
#else
#define AST()
#endif    // _DEBUG
#include <map>
#include <vector>
//#include <mutex>
#include <string>
#include <Windows.h>
#include "../VECTOR2.h"


//using namespace std;
using VEC_INT = std::vector<int>;
#define lpImageMng ImageMng::GetInstance()
#define IMAGE_ID(fmt, ...) (ImageMng::GetInstance().GetID(fmt, __VA_ARGS__))
class ImageMng
{
public:
	static ImageMng& GetInstance(void)
	{
		static ImageMng s_Instance;
		return s_Instance;
	}

	const int& GetID(std::wstring f_name);			//ﾒﾓﾘの取得
	const VEC_INT& GetID(std::wstring f_name, VECTOR2 divSize, VECTOR2 divCnt);			//画像の分割読み込み

private:
	ImageMng();
	~ImageMng();
	ImageMng(ImageMng&) = delete;
	ImageMng operator=(ImageMng&) = delete;
	//std::map<ｷｰの型,連想型配列の型> 連想配列名;
	//std::map<std::string, std::vector<int>> imgMap;
	std::map<std::wstring, VEC_INT> imgMap;
};
