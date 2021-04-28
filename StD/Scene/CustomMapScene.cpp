#include <DxLib.h>
#include <list>
#include "TitleScene.h"
#include "../Application.h"
#include "CustomMapScene.h"
#include "../Mng/ImageMng.h"
#include "../MouseController.h"
#include "../StringUtil.h"
#define CUSTOM dynamic_cast<Custom*>(map_)
CustomMapScene::CustomMapScene()
{
	Init();
}

CustomMapScene::~CustomMapScene()
{
}

unique_Base CustomMapScene::Update(unique_Base own)
{
	now = lpKeyController.GetCtl(KEY_TYPE::NOW);
	old = lpKeyController.GetCtl(KEY_TYPE::OLD);
	
	if ((now[KEY_INPUT_SPACE]) & (~old[KEY_INPUT_SPACE]))
	{
		return std::make_unique<TitleScene>();
	}

	updateFunc_[nowState_]();
	return std::move(own);
}

bool CustomMapScene::Init()
{
	
		map_ = std::make_unique<Custom>(VECTOR2());
		nowState_ = CustomState::SET_STATE;
		// update�n�֐��ۑ�
		updateFunc_.try_emplace(CustomState::SET_STATE, std::bind(&CustomMapScene::SetStateUpdate, this));
		updateFunc_.try_emplace(CustomState::MAP_CUSTOM, std::bind(&CustomMapScene::Map_CuntomUpdate, this));
		updateFunc_.try_emplace(CustomState::END_CUSTOM, std::bind(&CustomMapScene::EndCustomUpdate, this));
		// draw�n�֐��ۑ�
		drawFunc_.try_emplace(CustomState::SET_STATE, std::bind(&CustomMapScene::SetStateDraw, this));
		drawFunc_.try_emplace(CustomState::MAP_CUSTOM, std::bind(&CustomMapScene::MapCustomDraw, this));
		drawFunc_.try_emplace(CustomState::END_CUSTOM, std::bind(&CustomMapScene::EndCustomDraw, this));
		const int bSize = 64;
		const int bSpace = 20;
		bPosList_.push_back({ VECTOR2(SELECT_UI_POS.first.x + bSpace,bSpace),VECTOR2(SELECT_UI_POS.first.x + bSize + bSpace, bSize + bSpace) });
		bPosList_.push_back({ VECTOR2(SELECT_UI_POS.first.x + bSpace + (bSize + bSpace),bSpace),VECTOR2(SELECT_UI_POS.first.x + bSize + bSpace + (bSize + bSpace), bSize + bSpace) });
		bPosList_.push_back({ VECTOR2(SELECT_UI_POS.first.x + bSpace + (bSize + bSpace)*2,bSpace),VECTOR2(SELECT_UI_POS.first.x + bSize + bSpace + (bSize + bSpace)*2, bSize + bSpace) });
		bPosList_.push_back({ VECTOR2(SELECT_UI_POS.first.x + bSpace,bSpace+(bSize+bSpace)),VECTOR2(SELECT_UI_POS.first.x + bSize + bSpace, bSize + bSpace+ (bSize + bSpace)) });
		bPosList_.push_back({ VECTOR2(SELECT_UI_POS.first.x + bSpace+ (bSize + bSpace),bSpace+(bSize+bSpace)),VECTOR2(SELECT_UI_POS.first.x + bSize + bSpace+ (bSize + bSpace), bSize + bSpace+ (bSize + bSpace)) });
		bPosList_.push_back({ VECTOR2(SELECT_UI_POS.first.x + bSpace+ (bSize + bSpace)*2,bSpace+(bSize+bSpace)),VECTOR2(SELECT_UI_POS.first.x + bSize + bSpace+ (bSize + bSpace)*2, bSize + bSpace+ (bSize + bSpace)) });



		mapSizeX_ = 0;
		mapSizeY_ = 0;
		fileName_[0] = TCHAR();
		blendAlpha_ = 256;
		selChip_ = MapChipName::FIELD;
		LoadText();
	return true;
}

void CustomMapScene::Draw()
{
	Vec2Float cPos= Application::Instance().GetCamera().GetPos();
	cPos *= 2.0f;
	//DrawString(100, 100, L"CustomMapScene", 0xffffff);
	VECTOR2 mPos = lpMouseController.GetPos();

	if (nowState_ == CustomState::MAP_CUSTOM)
	{
#ifdef _DEBUG
	DrawFormatString(mPos.x+cPos.x, mPos.y+cPos.y-10, 0xffffff, L"%d", static_cast<int>(map_->GetMapChip((mPos + cPos))));
#endif // DEBUG

		map_->Draw();
		
		if (!lpMouseController.IsHitBoxToMouse(SELECT_UI_POS.first, SELECT_UI_POS.second) && !lpMouseController.IsHitBoxToMouse(TEXT_UI_POS.first, TEXT_UI_POS.second))
		{
			if (lpMouseController.IsHitBoxToMouse(VECTOR2(0, 0)-cPos, map_->GetMapSize() * map_->GetChipSize() -cPos))
			{
				mPos = (mPos+cPos) / (map_->GetChipSize()) * (map_->GetChipSize());
				SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA,std::abs(128- blendAlpha_%256));
				DrawBox(mPos.x, mPos.y, (mPos.x) + map_->GetChipSize().x, (mPos.y) + map_->GetChipSize().y, 0xcccc00, true);
				SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

			}
		}
	}


}

void CustomMapScene::DrawUI()
{
	drawFunc_[nowState_]();
	
}

void CustomMapScene::SetStateUpdate()
{
	if ((now[KEY_INPUT_BACK]) & (~old[KEY_INPUT_BACK]))
	{
		//nowState_ = CustomState::MAP_CUSTOM;
	}
}

void CustomMapScene::Map_CuntomUpdate()
{
	if ((now[KEY_INPUT_BACK]) & (~old[KEY_INPUT_BACK]))
	{
		nowState_ = CustomState::END_CUSTOM;
	}
	VECTOR2 mPos;
	GetMousePoint(&mPos.x, &mPos.y);
	auto cPos = lpApplication.GetCamera().GetPos()*2.0f;
	if (lpMouseController.GetClicking())
	{
		if (mPos.x > SELECT_UI_POS.first.x)
		{

		}
		else
		{
			map_->SetChip(cPos + mPos , selChip_);
		}
	}
	blendAlpha_+=2;

}

void CustomMapScene::EndCustomUpdate()
{
	if ((now[KEY_INPUT_BACK]) & (~old[KEY_INPUT_BACK]))
	{
		nowState_ = CustomState::SET_STATE;
	}
}

void CustomMapScene::SetStateDraw()
{
	DrawString(0, 0, L"Set", 0xffffff);
	DrawString(0, STRING_HIGHT, L"�}�b�v�̉����F", 0xffffff);
	DrawString(0, STRING_HIGHT+LINE_SPACING, L"�}�b�v�̍����F", 0xffffff);
	DrawString(0, STRING_HIGHT + LINE_SPACING*2, L"�t�@�C�����F", 0xffffff);
	DrawString(0, STRING_HIGHT*2 + LINE_SPACING*2, L"�����̕����ƃX�y�[�X�͎g�p�ł��܂���\n�u���@�^�@�F�@���@�H�@�h�@���@���@�b�@.�@& ( ) [ ] { } ^ = ; ! ' + , ` ~�v", 0xff9999);
	int tmpFlag = 0;
	// ��������
	mapSizeX_ = KeyInputNumber(GetDrawStringWidth(L"�}�b�v�̉����F", GetStringLength(L"�}�b�v�̉����F")) + 1, STRING_HIGHT, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	if (mapSizeX_<MIN_MAP_SIZE || mapSizeX_>MAX_MAP_SIZE)
	{
		return;
	}
	else
	{
		tmpFlag++;
	}
	DrawFormatString(GetDrawStringWidth(L"�}�b�v�̉����F", GetStringLength(L"�}�b�v�̉����F")) + 1, STRING_HIGHT, 0xffffff, L"%d", mapSizeX_);
	// �c������
	mapSizeY_ = KeyInputNumber(GetDrawStringWidth(L"�}�b�v�̍����F", GetStringLength(L"�}�b�v�̍����F")) + 1, STRING_HIGHT+LINE_SPACING, MAX_MAP_SIZE, MIN_MAP_SIZE, true);
	if (mapSizeY_<MIN_MAP_SIZE || mapSizeY_>MAX_MAP_SIZE)
	{
		return;
	}
	else
	{
		tmpFlag++;
	}
	DrawFormatString(GetDrawStringWidth(L"�}�b�v�̍����F", GetStringLength(L"�}�b�v�̍����F")) + 1, STRING_HIGHT + LINE_SPACING, 0xffffff, L"%d", mapSizeY_);
	// ���O����
	if (KeyInputString(GetDrawStringWidth(L"�t�@�C�����F", GetStringLength(L"�t�@�C�����F")) + 1, STRING_HIGHT+LINE_SPACING*2, MAX_NAME_SIZE, fileName_, true) != 1)
	{
		return;
	}
	else {
		// �t�@�C�����ɔ�Ή��������܂܂�Ă��邩
		if (FileNameErrorCheck(fileName_))
		{
			return;
		}
		tmpFlag++;
	}
	if (tmpFlag >= 3)
	{
		nowState_= CustomState::MAP_CUSTOM;
		dynamic_cast<Custom*>(map_.get())->SetUp(fileName_, VECTOR2(mapSizeX_, mapSizeY_));
	}
}

void CustomMapScene::MapCustomDraw()
{
	//DrawString(0, 0, L"Custom", 0xffffff);
	// �g�\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawRoundRect(SELECT_UI_POS.first.x, SELECT_UI_POS.first.y, SELECT_UI_POS.second.x, SELECT_UI_POS.second.y,20,20, 0x555555, true);
	DrawRoundRect(SELECT_UI_POS.first.x, SELECT_UI_POS.first.y, SELECT_UI_POS.second.x, SELECT_UI_POS.second.y, 20, 20, 0xffffff, false);
	DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0x555555, true);
	DrawRoundRect(TEXT_UI_POS.first.x, TEXT_UI_POS.first.y, TEXT_UI_POS.second.x, TEXT_UI_POS.second.y, 20, 20, 0xffffff, false);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	// �������̕\��
	DrawString(TEXT_UI_POS.first.x+30, TEXT_UI_POS.first.y+ (TEXT_UI_POS.second.y - TEXT_UI_POS.first.y) / 5,_StW(textData_[selChip_]).c_str(), 0xffffff);
	VECTOR2 mPos = lpMouseController.GetPos();
	// �Ƃ肠�����{�^���̕\��
	int shadowOffset = 3;
	int pushuOffset = 1;
	for (auto list : bPosList_)
	{
	if (lpMouseController.GetClicking())
	{
		if (lpMouseController.IsHitBoxToMouse(SELECT_UI_POS.first,SELECT_UI_POS.second))
		{
			DrawRoundRect(list.first.x+ pushuOffset, list.first.y+ pushuOffset, list.second.x+ pushuOffset, list.second.y+ pushuOffset, 10, 10, 0xffffff, true);
		}
		else
		{
			DrawRoundRect(list.first.x+ shadowOffset, list.first.y+ shadowOffset, list.second.x+ shadowOffset, list.second.y+ shadowOffset, 10, 10, 0x000000, true);
			DrawRoundRect(list.first.x, list.first.y, list.second.x, list.second.y, 10, 10, 0xffffff, true);
		}
	}
	else {
		DrawRoundRect(list.first.x + shadowOffset, list.first.y + shadowOffset, list.second.x + shadowOffset, list.second.y + shadowOffset, 10, 10, 0x000000, true);
		DrawRoundRect(list.first.x, list.first.y, list.second.x, list.second.y, 10, 10, 0xffffff, true);
	}

	}
#ifdef _DEBUG

	DrawFormatString(mPos.x, mPos.y+10, 0x00ff00, L"%d:%d", mPos.x, mPos.y);
	DrawFormatString(mPos.x, mPos.y + 30, 0x0000ff, L"%d:%d", mPos.x + static_cast<int>(lpApplication.GetCamera().GetPos().x), mPos.y + static_cast<int>(lpApplication.GetCamera().GetPos().y));
#endif // _DEBUG




}

void CustomMapScene::EndCustomDraw()
{
	DrawString(0, 0, L"End", 0xffffff);

}

bool CustomMapScene::FileNameErrorCheck(std::wstring fileName)
{
	//���@�^�@�F�@���@�H�@�h�@���@���@�b
	auto check = [](TCHAR code) {
		std::list<TCHAR> wErrorCode = { L'\\',L'/',L':',L'*',L'?',L'<',L'>',L'|',L' ',L'.' };	// Windows�̃t�@�C���Ɏg�p�ł��Ȃ�����
		std::list<TCHAR> cErrorCode = { L'&', L'(',L')', L'[',L']' ,L'{',L'}', L'^', L'=', L';', L'!',L'\'', L'+', L',', L'`', L'~' };	// ���łɔO�̂��ߏȂ��Ă���
		for (auto error : wErrorCode)
		{
			if (code == error)
			{
				return true;
			}
		}
		for (auto error : cErrorCode)
		{
			if (code == error)
			{
				return true;
			}
		}
		return false;
	};

	for (int f = 0; f < MAX_NAME_SIZE; f++)
	{
		// Windows�̃G���[�R�[�h�������ꍇ
		if (check(fileName.c_str()[f]))
		{
			return true;
		}
		// ���g���󂾂����ꍇ
		if (fileName.c_str()[0] == TCHAR())
		{
			return true;
		}
	}


	return false;
}

bool CustomMapScene::LoadText()
{
	tinyxml2::XMLDocument doc;
	auto error=doc.LoadFile("data/textData.xml");
	if (error != tinyxml2::XML_SUCCESS)
	{
		return false;
	}
	textData_.try_emplace( MapChipName::MAINSTAY ,doc.FirstChildElement("mainstay")->GetText() );
	textData_.try_emplace( MapChipName::SPAWNER ,doc.FirstChildElement("spawner")->GetText() );
	textData_.try_emplace( MapChipName::ROOT ,doc.FirstChildElement("root")->GetText() );
	textData_.try_emplace( MapChipName::FIELD ,doc.FirstChildElement("field")->GetText() );
	textData_.try_emplace( MapChipName::WALL ,doc.FirstChildElement("wall")->GetText() );

	return true;
}