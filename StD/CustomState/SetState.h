#pragma once
#include "CustomState.h"
#include "../Scene/CustomMapScene.h"
struct SetState:public CustomStateBase
{
	SetState() {};
	~SetState() {};
	bool Init(CustomMapScene*scene)override
	{
		const int buttonSize = 50;
		const VECTOR2 defPos(20,20);
		inputcnt_ = 0;
		inputNum_.resize(4);
		inputNum_[0] = "10";
		inputNum_[1] = "10";
		for (int a = 0; a <= 10; a++)
		{
			buttonList_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(defPos.x + (buttonSize + 5) * (a % 5),defPos.y + (buttonSize + 5) * (a / 5)),
				VECTOR2(defPos.x + (buttonSize + 5) * (a % 5) + buttonSize, defPos.y + buttonSize + (buttonSize + 5) * (a / 5)), 
				VECTOR2(10, 10), 0xffffff, [&, a]() {
					if (inputcnt_ < 2)
					{
						inputNum_[inputcnt_] = std::to_string(10 + a); 
					} 
			return true; }, VECTOR2()));
			buttonList_.back()->SetString(std::to_string(10+a), VECTOR2(5, 5), CreateFontToHandle(NULL, 40, 9, DX_FONTTYPE_ANTIALIASING));
			buttonList_.back()->SetAuto();
			buttonList_.back()->SetTag(1);
		}
		buttonList_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(defPos.x + (buttonSize + 5) * (11 % 5), defPos.y + (buttonSize + 5) * (11 / 5)),
			VECTOR2(defPos.x + (buttonSize + 5) * (11 % 5) + buttonSize * 2 + 5, defPos.y + buttonSize + (buttonSize + 5) * (11 / 5)),
			VECTOR2(10, 10), 0xffffff, [&]() {inputcnt_ -= (inputcnt_ <=0 ? 0 : 1); return true; }, VECTOR2()));
		buttonList_.back()->SetString("back", VECTOR2(5, 5), CreateFontToHandle(NULL, 40, 9, DX_FONTTYPE_ANTIALIASING));
		buttonList_.back()->SetAuto();
		buttonList_.back()->SetTag(1);
		buttonList_.emplace_back(std::make_unique<RoundRectButton>(VECTOR2(defPos.x + (buttonSize + 5) * (13 % 5), defPos.y + (buttonSize + 5) * (13 / 5)),
			VECTOR2(defPos.x + (buttonSize + 5) * (13 % 5) + buttonSize * 2 + 5, defPos.y + buttonSize + (buttonSize + 5) * (13 / 5)),
			VECTOR2(10, 10), 0xffffff, [&]() {
				inputcnt_ += (inputcnt_ >= 3 ? 0 : 1);
				if (inputcnt_ == 2) { SetActiveKeyInput(keyhandle_); }
				return true; }, VECTOR2()));
		buttonList_.back()->SetString("next", VECTOR2(5,5),CreateFontToHandle(NULL,40,9,DX_FONTTYPE_ANTIALIASING));
		buttonList_.back()->SetAuto();
		buttonList_.back()->SetTag(1);
		fontHandle_ = CreateFontToHandle(NULL, 30, 9);
		keyhandle_ = MakeKeyInput(20, false, false,false);
		return true;
	}
	void Update(CustomMapScene *scene)override
	{
		for (auto&& list : buttonList_)
		{
			if (inputcnt_ >= 2 && list->GetTag()>=1)
			{

			}
			else
			{
				list->Update();
			}
			
		}
		if (scene->now[KEY_INPUT_RETURN]&&CheckKeyInput(keyhandle_) == 1)
		{
			inputcnt_++;
			if (scene->FileNameErrorCheck(_StW(inputNum_[2])))
			{
				// エラー
				inputNum_[2] = "";
				SetKeyInputString(L"", keyhandle_);
				SetActiveKeyInput(keyhandle_);
				inputcnt_ = 0;
				return; 
			}
			scene->nowState_ = CustomState::MAP_CUSTOM;
			scene->map_->SetUp(_StW(inputNum_[2]), VECTOR2(std::atoi(inputNum_[0].c_str()), std::atoi(inputNum_[1].c_str())));
			scene->custom_[scene->nowState_]->Init(scene);
			Delete();

		}
	}
	void Draw(CustomMapScene* scene)override
	{
		VECTOR2 sSize;
		int bit;
		GetScreenState(&sSize.x, &sSize.y, &bit);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 128);
		DrawRoundRect(0, 0, sSize.x, sSize.y, 30, 30, 0xffffff, true);
		DrawRoundRect(0, 0, sSize.x, sSize.y, 30, 30, 0x000000, false);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
		for (auto&& list : buttonList_)
		{
			if (inputcnt_ >= 2 && list->GetTag() >= 1)
			{

			}
			else
			{
				list->Draw();
			}

		}		DrawStringToHandle(350, 50, _StW("マップの横のマス数:" + (inputNum_[0])).c_str(), 0x000000, fontHandle_);
		DrawStringToHandle(350, 50 + GetFontSizeToHandle(fontHandle_), _StW("マップの縦のマス数:" + (inputNum_[1])).c_str(), 0x000000, fontHandle_);
		DrawStringToHandle(350, 50 + GetFontSizeToHandle(fontHandle_) * 2, _StW("ファイル名\n"+(inputNum_[2])).c_str(), 0x00000, fontHandle_);
		DrawString(350,  50+GetFontSizeToHandle(fontHandle_)*4, L"※次の文字とスペースは使用できません\n「￥　／　：　＊　？　”　＜　＞　｜　.\n     　& ( ) [ ] { } ^ = ; ! ' + , ` ~」", 0xff9999);
		if (inputcnt_ == 0)
		{
			const int xsize = GetDrawStringWidthToHandle(L"マップの横のマス数:", GetStringLength(L"マップの横のマス数:"), fontHandle_);
			DrawBox(350 + xsize, 50, 350 + xsize + GetFontSizeToHandle(fontHandle_) * 2, 50 + GetFontSizeToHandle(fontHandle_), 0xff0000, false);
		}
		else if(inputcnt_==1)
		{
			const int ysize= GetDrawStringWidthToHandle(L"マップの縦のマス数:", GetStringLength(L"マップの縦のマス数:"), fontHandle_);
			DrawBox(350 + ysize, 50 + GetFontSizeToHandle(fontHandle_), 350 + ysize + GetFontSizeToHandle(fontHandle_) * 2, 50 + GetFontSizeToHandle(fontHandle_)*2, 0xff0000, false);
		}
		else if(inputcnt_==2)
		{
			TCHAR str[21];
			GetKeyInputString(str, keyhandle_);
			std::wstring wstr = str;
			inputNum_[inputcnt_] = _WtS(wstr);
			DrawBox(350, 50 + GetFontSizeToHandle(fontHandle_) * 3, 350 + GetDrawStringWidthToHandle(_StW(inputNum_[inputcnt_]).c_str(),GetStringLength(_StW(inputNum_[inputcnt_]).c_str()),fontHandle_), 50 + GetFontSizeToHandle(fontHandle_) * 4, 0xff0000, false);
			//DrawKeyInputModeString(350, 50 + GetFontSizeToHandle(fontHandle_) * 3);
			//DrawKeyInputString(350, 50 + GetFontSizeToHandle(fontHandle_) * 3, keyhandle_);
			

		}
		else if(inputcnt_ ==3)
		{

		}


	}
	void Delete() {
		fileList_.clear();
		buttonList_.clear();
		isNewCreate_ = false;
		inputcnt_ = 0;
		DeleteFontToHandle(fontHandle_);
		DeleteLightHandle(keyhandle_);
	}
private:
	void NewCreate()
	{

		//DrawString(0, 0, L"Set", 0xffffff);
	//DrawString(0, STRING_HIGHT, L"マップの横幅：", 0xffffff);
	//DrawString(0, STRING_HIGHT + LINE_SPACING, L"マップの高さ：", 0xffffff);
	//DrawString(0, STRING_HIGHT + LINE_SPACING * 2, L"ファイル名：", 0xffffff);
	//DrawString(0, STRING_HIGHT * 2 + LINE_SPACING * 2, L"※次の文字とスペースは使用できません\n「￥　／　：　＊　？　”　＜　＞　｜　.　& ( ) [ ] { } ^ = ; ! ' + , ` ~」", 0xff9999);
	//int tmpFlag = 0;
	//// 横幅入力
	//scene->mapSizeX_ = KeyInputNumber(GetDrawStringWidth(L"マップの横幅：", GetStringLength(L"マップの横幅：")) + 1, STRING_HIGHT, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	//if (scene->mapSizeX_<MIN_MAP_SIZE || scene->mapSizeX_>MAX_MAP_SIZE)
	//{
	//	return;
	//}
	//else
	//{
	//	tmpFlag++;
	//}
	//DrawFormatString(GetDrawStringWidth(L"マップの横幅：", GetStringLength(L"マップの横幅：")) + 1, STRING_HIGHT, 0xffffff, L"%d", scene->mapSizeX_);
	//// 縦幅入力
	//scene->mapSizeY_ = KeyInputNumber(GetDrawStringWidth(L"マップの高さ：", GetStringLength(L"マップの高さ：")) + 1, STRING_HIGHT + LINE_SPACING, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	//if (scene->mapSizeY_<MIN_MAP_SIZE || scene->mapSizeY_>MAX_MAP_SIZE)
	//{
	//	return;
	//}
	//else
	//{
	//	tmpFlag++;
	//}
	//DrawFormatString(GetDrawStringWidth(L"マップの高さ：", GetStringLength(L"マップの高さ：")) + 1, STRING_HIGHT + LINE_SPACING, 0xffffff, L"%d", scene->mapSizeY_);
	//// 名前入力
	//if (KeyInputString(GetDrawStringWidth(L"ファイル名：", GetStringLength(L"ファイル名：")) + 1, STRING_HIGHT + LINE_SPACING * 2, MAX_NAME_SIZE, scene->fileName_, true) != 1)
	//{
	//	return;
	//}
	//else {
	//	// ファイル名に非対応文字が含まれているか
	//	if (scene->FileNameErrorCheck(scene->fileName_))
	//	{
	//		return;
	//	}
	//	tmpFlag++;
	//}
	//if (tmpFlag >= 3)
	//{
	//	scene->nowState_ = CustomState::MAP_CUSTOM;
	//	scene->map_->SetUp(scene->fileName_, VECTOR2(scene->mapSizeX_, scene->mapSizeY_));
	//	scene->custom_[scene->nowState_]->Init(scene);
	//	
	//	
	//}
	}
	// ファイル名のリスト格納用
	std::list<std::string>fileList_;
	std::list<std::unique_ptr<Button>>buttonList_;
	bool isNewCreate_;
	int inputcnt_;
	// 
	std::vector<std::string>inputNum_;
	int fontHandle_;
	// キー入力用ハンドル
	int keyhandle_;
};