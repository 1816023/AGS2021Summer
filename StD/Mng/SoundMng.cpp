#include <DxLib.h>
#include "SoundMng.h"
#include "../StringUtil.h"


const int& SoundMng::GetID(std::string f_name)
{
	// map‚É±¸¾½‚µ‚½uŠÔÃŞ°À¶‚ª‚È‚©‚Á‚½‚çƒƒ‚ƒŠ‚ğŠm•Û‚µ‚Ä‚»‚Ì’l‚ğ•Ô‚·
	if (sndMap_.find(f_name) == sndMap_.end())
	{
		sndMap_[f_name] = LoadSoundMem(_StW(f_name).c_str());
		if (sndMap_[f_name] == -1)
		{
			AST();
		}
	}
	return sndMap_[f_name];
}

const int& SoundMng::StartSound(std::string f_name, PlayType type)
{
	return PlaySoundMem(GetID(f_name),static_cast<int>(type));
}


const int& SoundMng::StopSound(std::string f_name)
{
	return StopSoundMem(GetID(f_name));
}

const int& SoundMng::StopSoundAll()
{
	int error = 0;
	for (auto sound : sndMap_)
	{
		if (CheckSoundMem(sound.second))
		{
			error|=StopSoundMem(sound.second);
		}
	}
	return error;
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
	for (auto&& handle : sndMap_)
	{
		DeleteSoundMem(handle.second);
	}
	sndMap_.clear();
}

SoundMng::SoundMng()
{
}


SoundMng::~SoundMng()
{
}