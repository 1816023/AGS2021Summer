#pragma once
#include <map>
#include <vector>
#include <string>
//ﾃﾞﾊﾞｯｸ用の定理
#ifdef _DEBUG
#define AST(){\
	TCHAR ast_mes[256];\
	wsprintf(ast_mes, L"%s %d行目￥0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, L"ｱｻｰﾄ表示", MB_OK);\
	}
#else
#define AST()
#endif    // _DEBUG

using VEC_INT = std::vector<int>;
#define lpSoundMng SoundMng::GetInstance()
#define Sound_ID(X) (SoundMng::GetInstance().GetID(X))

class SoundMng
{
public:
	static SoundMng& GetInstance(void)
	{
		static SoundMng s_Instance;
		return (s_Instance);
	}
	const int& GetID(std::string f_name);		// SEﾊﾝﾄﾞﾙの入手
	const int& StartSound(std::string f_name, int soundType);
	const int& StopSound(std::string f_name);
	const int& ChangeVol(int vol, std::string f_name);
	const int& CheckSound(std::string f_name);
private:
	SoundMng();
	~SoundMng();
	SoundMng(SoundMng&) = delete;
	void operator=(SoundMng&)= delete;
	std::map<std::string, int> sndMap;

};
