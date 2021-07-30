#pragma once
#include "CustomState.h"
struct RootCustom :
	public CustomStateBase
{
	RootCustom() {};
	~RootCustom()override {};
	bool Init(CustomMapScene* scene) override
	{
		dirChip_ = RootDir::MAX;
		const TCHAR* fontName = L"rootButton";
		const int bSize = 64;
		const int bSpace = 20;
		VECTOR2 roundS = { 10, 10 };
		lpFontMng.AddStrFont(bSize, fontName);

		auto* button =(new RoundRectButton(VECTOR2(bSpace, bSpace * 2), VECTOR2(bSize, bSize), roundS, 0x007fff, [&]() {dirChip_ = RootDir::UP; return true; }));
		button->SetAuto();
		button->SetReversePush();
		button->SetString("ª", VECTOR2(),lpFontMng.GetStrFont(fontName));
		scene->canvas_->AddUIByID(button, 0);
		button = (new RoundRectButton(VECTOR2(bSize + bSpace * 2, bSpace * 2), VECTOR2(bSize, bSize), roundS, 0xff0f0f, [&]() {dirChip_ = RootDir::DOWN; return true; }));
		button->SetAuto();
		button->SetReversePush();
		button->SetString("«", VECTOR2(), lpFontMng.GetStrFont(fontName));
		scene->canvas_->AddUIByID(button, 0);
		button = (new RoundRectButton(VECTOR2(bSize * 2 + bSpace * 3, bSpace * 2), VECTOR2(bSize, bSize), roundS, 0xfff00, [&]() {dirChip_ = RootDir::RIGHT; return true; }));
		button->SetAuto();
		button->SetReversePush();
		button->SetString("¨", VECTOR2(), lpFontMng.GetStrFont(fontName));
		scene->canvas_->AddUIByID(button, 0);
		button = (new RoundRectButton(VECTOR2(bSpace, bSize + bSpace * 3), VECTOR2(bSize, bSize), roundS, 0xe3e3e3, [&]() {dirChip_ = RootDir::LEFT; return true; }));
		button->SetAuto();
		button->SetReversePush();
		button->SetString("©", VECTOR2(), lpFontMng.GetStrFont(fontName));
		scene->canvas_->AddUIByID(button, 0);
		return true;
	}
	void Update(CustomMapScene* scene) override
	{

	}
	void Draw(CustomMapScene* scene) override
	{
		
	}
	void Delete() override
	{

	}
private:
	RootDir dirChip_;

};

