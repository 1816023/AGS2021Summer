#pragma once
#include "../File/FileSystem.h"
#include "CustomState.h"
#include "../Scene/CustomMapScene.h"
#include "../tinyxml2/tinyxml2.h"
struct DataState
{
	std::string fileName;
	VECTOR2 mapSize;
	
};
struct SetState:public CustomStateBase
{
	SetState() {};
	~SetState() {};
	bool Init(CustomMapScene*scene)
	{
		scene->mapSizeX_ = 0;
		scene->mapSizeY_ = 0;
		scene->fileName_[0] = TCHAR();
		FileSystem::serch("data/mapData",fileList_);

		return true;
	}
	void Update(CustomMapScene *scene)
	{

	}
	void Draw(CustomMapScene* scene)
	{

		DrawString(0, 0, L"Set", 0xffffff);
		DrawString(0, STRING_HIGHT, L"マップの横幅：", 0xffffff);
		DrawString(0, STRING_HIGHT + LINE_SPACING, L"マップの高さ：", 0xffffff);
		DrawString(0, STRING_HIGHT + LINE_SPACING * 2, L"ファイル名：", 0xffffff);
		DrawString(0, STRING_HIGHT * 2 + LINE_SPACING * 2, L"※次の文字とスペースは使用できません\n「￥　／　：　＊　？　”　＜　＞　｜　.　& ( ) [ ] { } ^ = ; ! ' + , ` ~」", 0xff9999);
		int tmpFlag = 0;
		// 横幅入力
		scene->mapSizeX_ = KeyInputNumber(GetDrawStringWidth(L"マップの横幅：", GetStringLength(L"マップの横幅：")) + 1, STRING_HIGHT, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
		if (scene->mapSizeX_<MIN_MAP_SIZE || scene->mapSizeX_>MAX_MAP_SIZE)
		{
			return;
		}
		else
		{
			tmpFlag++;
		}
		DrawFormatString(GetDrawStringWidth(L"マップの横幅：", GetStringLength(L"マップの横幅：")) + 1, STRING_HIGHT, 0xffffff, L"%d", scene->mapSizeX_);
		// 縦幅入力
		scene->mapSizeY_ = KeyInputNumber(GetDrawStringWidth(L"マップの高さ：", GetStringLength(L"マップの高さ：")) + 1, STRING_HIGHT + LINE_SPACING, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
		if (scene->mapSizeY_<MIN_MAP_SIZE || scene->mapSizeY_>MAX_MAP_SIZE)
		{
			return;
		}
		else
		{
			tmpFlag++;
		}
		DrawFormatString(GetDrawStringWidth(L"マップの高さ：", GetStringLength(L"マップの高さ：")) + 1, STRING_HIGHT + LINE_SPACING, 0xffffff, L"%d", scene->mapSizeY_);
		// 名前入力
		if (KeyInputString(GetDrawStringWidth(L"ファイル名：", GetStringLength(L"ファイル名：")) + 1, STRING_HIGHT + LINE_SPACING * 2, MAX_NAME_SIZE, scene->fileName_, true) != 1)
		{
			return;
		}
		else {
			// ファイル名に非対応文字が含まれているか
			if (scene->FileNameErrorCheck(scene->fileName_))
			{
				return;
			}
			tmpFlag++;
		}
		if (tmpFlag >= 3)
		{
			scene->nowState_ = CustomState::MAP_CUSTOM;
			scene->map_->SetUp(scene->fileName_, VECTOR2(scene->mapSizeX_, scene->mapSizeY_));
			scene->custom_[scene->nowState_]->Init(scene);
			
			
		}
	}
private:
	// 
	DataState GetData(std::string path) {
		tinyxml2::XMLDocument doc;
		doc.LoadFile(path.c_str());

	}
	// ファイル名のリスト格納用
	std::list<std::string>fileList_;
	std::list<Button>ButtomList_;
};