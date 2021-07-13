#include "Canvas.h"
#include <assert.h>
#include <DxLib.h>
#include "UI.h"

struct UIStat
{
	UI* ui;			// ui本体
	int id;				// id
	std::wstring name;	// 名前
};


Canvas::Canvas(VECTOR2 pos, VECTOR2 size)
{
	pos_ = pos;
	size_ = size;
	color_ = 0xffffff;
}

Canvas::~Canvas()
{
}

void Canvas::AddUIByID(UI* ui, Justified just, int id)
{
	UIStat uiStat;
	uiStat.ui = ui;
	uiStat.ui->SetPos(PosToJustified(just, ui->GetSize()));
	uiStat.id = id;
	uiStat.name = L"";
	UIList_.emplace_back(uiStat);
}

void Canvas::AddUIByID(UI* ui, VECTOR2& pos, int id)
{
	UIStat uiStat;
	uiStat.ui = ui;
	uiStat.ui->SetPos(pos);
	uiStat.id = id;
	uiStat.name = L"";
	UIList_.emplace_back(uiStat);
}

void Canvas::AddUIByName(UI* ui, Justified just, std::wstring name)
{
	UIStat uiStat;
	uiStat.ui = ui;
	uiStat.ui->SetPos(PosToJustified(just, ui->GetSize()));
	uiStat.id = -1;
	uiStat.name = name;
	UIList_.emplace_back(uiStat);
}

void Canvas::AddUIByName(UI* ui, VECTOR2& pos, std::wstring name)
{
	UIStat uiStat;
	uiStat.ui = ui;
	uiStat.ui->SetPos(pos);
	uiStat.id = -1;
	uiStat.name = name;
	UIList_.emplace_back(uiStat);
}

UI* Canvas::GetUIByName(std::wstring name)
{
	auto find = std::find_if(UIList_.begin(), UIList_.end(), [name](const UIStat& uis) {return uis.name == name; });
	if (find != UIList_.end())
	{
		return (*find).ui;
	}
	return nullptr;
}

UI* Canvas::GetUIByName(int id)
{
	auto find = std::find_if(UIList_.begin(), UIList_.end(), [id](const UIStat& uis) {return uis.id == id; });
	if (find != UIList_.end())
	{
		return (*find).ui;
	}
	return nullptr;
}

void Canvas::SetColor(int color)
{
	color_ = color;
}

void Canvas::Draw()
{
	DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, color_, true);
	for (auto ui : UIList_)
	{
		ui.ui->Draw();
	}
}

void Canvas::Update()
{
	for (auto ui : UIList_)
	{
		ui.ui->Update();
	}
}

VECTOR2 Canvas::PosToJustified(const Justified& just, const VECTOR2& size)
{
	VECTOR2 tmp = {};
	switch (just)
	{
	case Justified::CENTER:
		tmp = Center(size);
		break;
	case Justified::CENTER_UP:
		tmp = VECTOR2(Center(size).x, Up(size).y);
		break;
	case Justified::CENTER_DOWN:
		tmp = VECTOR2(Center(size).x ,Down(size).y);
		break;
	case Justified::CENTER_LEFT:
		tmp = VECTOR2(Left(size).x, Center(size).y);
		break;
	case Justified::LEFT_UP:
		tmp = Left(size) + Up(size);
		break;
	case Justified::LEFT_DOWN:
		tmp = Left(size) + Down(size);
		break;
	case Justified::CENTER_RIGHT:
		tmp = VECTOR2(Right(size).x, Center(size).y);
		break;
	case Justified::RIGHT_UP:
		tmp = Right(size) + Up(size);
		break;
	case Justified::RIGHT_DOWN:
		tmp = Right(size) + Down(size);
		break;
	default:
		// 異常値だとアサート
		assert(false);
		break;
	}
	return tmp;
}

VECTOR2 Canvas::Center(const VECTOR2& size)
{
	return (pos_ + size_ / 2) - size / 2;
}

VECTOR2 Canvas::Left(const VECTOR2& size)
{
	return VECTOR2(pos_.x, 0);
}

VECTOR2 Canvas::Right(const VECTOR2& size)
{
	return VECTOR2(pos_.x + size_.x - size.x, 0);
}

VECTOR2 Canvas::Up(const VECTOR2& size)
{
	return VECTOR2(0, pos_.y);
}

VECTOR2 Canvas::Down(const VECTOR2& size)
{
	return  VECTOR2(0, pos_.y + size_.y - size.y);
}
