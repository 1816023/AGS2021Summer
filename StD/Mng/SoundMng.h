#pragma once
#include <map>
#include <vector>
#include <string>
//ÃŞÊŞ¯¸—p‚Ì’è—
#ifdef _DEBUG
#define AST(){\
	TCHAR ast_mes[256];\
	wsprintf(ast_mes, L"%s %ds–Ú0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, L"±»°Ä•\¦", MB_OK);\
	}
#else
#define AST()
#endif    // _DEBUG

using VEC_INT = std::vector<int>;
#define lpSoundMng SoundMng::GetInstance()
#define Sound_ID(X) (SoundMng::GetInstance().GetID(X))
enum class PlayType
{
	NORMAL = DX_PLAYTYPE_NORMAL,
	BACK = DX_PLAYTYPE_BACK,
	LOOP = DX_PLAYTYPE_LOOP
};
class SoundMng
{
public:
	static SoundMng& GetInstance(void)
	{
		static SoundMng s_Instance;
		return (s_Instance);
	}
	// SEÊİÄŞÙ‚Ì“üè
	const int& GetID(std::string f_name);	
	const int& StartSound(std::string f_name,PlayType type=PlayType::BACK);
	const int& StopSound(std::string f_name);
	const int& StopSoundAll();
	const int& ChangeVol(int vol, std::string f_name);
	const int& CheckSound(std::string f_name);
	void DeleteHandle();
private:
	SoundMng();
	~SoundMng();
	SoundMng(SoundMng&) = delete;
	void operator=(SoundMng&)= delete;
	std::map<std::string, int> sndMap_;

};
