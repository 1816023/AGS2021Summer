#include <DxLib.h>
#include "SoundMng.h"
#include "../StringUtil.h"


const int& SoundMng::GetID(std::string f_name)
{
	// map‚É±¸¾½‚µ‚½uŠÔÃŞ°À¶‚ª‚È‚©‚Á‚½‚çƒƒ‚ƒŠ‚ğŠm•Û‚µ‚Ä‚»‚Ì’l‚ğ•Ô‚·
	if (sndMap.find(f_name) == sndMap.end())
	{
		sndMap[f_name] = LoadSoundMem(_StW(f_name).c_str());
		if (sndMap[f_name] == -1)
		{
			AST();
		}
	}
	return sndMap[f_name];
}

const int& SoundMng::StartSound(std::string f_name, int soundType)
{
	return PlaySoundMem(GetID(f_name), soundType);
}

const int& SoundMng::StopSound(std::string f_name)
{
	return StopSoundMem(GetID(f_name));
}

const int& SoundMng::ChangeVol(int vol, std::string f_name)
{
	return ChangeVolumeSoundMem(255 * vol / 100, GetID(f_name));
}

const int& SoundMng::CheckSound(std::string f_name)
{
	return CheckSoundMem(GetID(f_name));
}

SoundMng::SoundMng()
{
}


SoundMng::~SoundMng()
{
}