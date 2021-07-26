#pragma once
#ifdef _DEBUG
#define AST(){\
	TCHAR ast_mes[256];\
	wsprintf(ast_mes, L"%s %d�s�ځ�0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, L"���ĕ\��", MB_OK);\
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

	const int& GetID(std::wstring f_name);			//��؂̎擾
	const VEC_INT& GetID(std::wstring f_name, VECTOR2 divSize, VECTOR2 divCnt);			//�摜�̕����ǂݍ���

private:
	ImageMng();
	~ImageMng();
	ImageMng(ImageMng&) = delete;
	ImageMng operator=(ImageMng&) = delete;
	//std::map<���̌^,�A�z�^�z��̌^> �A�z�z��;
	//std::map<std::string, std::vector<int>> imgMap;
	std::map<std::wstring, VEC_INT> imgMap;
};
