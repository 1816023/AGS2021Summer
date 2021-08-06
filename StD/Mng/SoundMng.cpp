#include <DxLib.h>
#include "SoundMng.h"
#include "../StringUtil.h"


const int& SoundMng::GetID(std::string f_name)
{
	// mapにｱｸｾｽした瞬間ﾃﾞｰﾀｶがなかったらメモリを確保してその値を返す
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

const int& SoundMng::StartSound(std::string f_name, PlayType type)
{
	return PlaySoundMem(GetID(f_name),static_cast<int>(type));
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

void SoundMng::DeleteHandle()
{
	for (auto&& handle : sndMap)
	{
		DeleteSoundMem(handle.second);
	}
	sndMap.clear();
}

SoundMng::SoundMng()
{
}


SoundMng::~SoundMng()
{
}