#include "Canvas.h"
#include <assert.h>
#include <DxLib.h>
#include "UI.h"
#include "../Mng/ImageMng.h"

struct UIStat
{
	UI* ui;			// ui本体
	int id;				// id
	std::wstring name;	// 名前
};


Canvas::Canvas(VECTOR2 pos, VECTOR2 size, int color, unsigned int alpha)
{
	Init();
	pos_ = pos;
	size_ = size;
	color_ = color;
	alpha_ = alpha;
}

Canvas::Canvas(VECTOR2 pos, VECTOR2 size, std::wstring path)
{
	Init();
	pos_ = pos;
	size_ = size;
	gHandle_ = IMAGE_ID(path);
}

Canvas::Canvas(VECTOR2 pos, VECTOR2 size, std::function<void(VECTOR2)> drawFunc)
{
	Init();
	pos_ = pos;
	size_ = size;
	drawFunc_ = drawFunc;
}

Canvas::Canvas(VECTOR2 pos, VECTOR2 size, BackType back)
{
	Init();
	pos_ = pos;
	size_ = size;
	backT_ = back;
}

Canvas::~Canvas()
{
	ClearUI();
}

void Canvas::AddUIByID(UI* ui, int id, Justified just)
{
	UIStat uiStat;
	uiStat.ui = ui;
	uiStat.ui->SetPos(PosToJustified(just, ui->GetSize()));
	uiStat.id = id;
	uiStat.name = L"";
	UIList_.emplace_back(uiStat);
}

void Canvas::AddUIByID(UI* ui, int id, VECTOR2 pos)
{
	UIStat uiStat;
	uiStat.ui = ui;
	uiStat.ui->SetPos(pos + pos_);
	uiStat.id = id;
	uiStat.name = L"";
	UIList_.emplace_back(uiStat);
}

void Canvas::AddUIByName(UI* ui, std::wstring name, Justified just)
{
	UIStat uiStat;
	uiStat.ui = ui;
	uiStat.ui->SetPos(PosToJustified(just, ui->GetSize()));
	uiStat.id = -1;
	uiStat.name = name;
	UIList_.emplace_back(uiStat);
}

void Canvas::AddUIByName(UI* ui, std::wstring name, VECTOR2 pos)
{
	UIStat uiStat;
	uiStat.ui = ui;
	uiStat.ui->SetPos(pos + pos_);
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

void Canvas::Init()
{
	pos_ = { 0,0 };
	size_ = { 0,0 };
	color_ = 0x000000;
	gHandle_ = -1;
	drawFunc_ = nullptr;
	backT_ = BackType::Non;
	isActive_ = true;
	alpha_ = 0;
}

void Canvas::Draw()
{
	if (!isActive_)
	{
		return;
	}
	BackDraw();
	for (auto ui : UIList_)
	{
		ui.ui->Draw();
	}
}

void Canvas::BackDraw()
{
	if (backT_ == BackType::Non)
	{
		return;
	}

	if (backT_ != BackType::Non)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawRoundRect(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 20, 20, 0x555555, true);
		DrawRoundRect(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 20, 20, 0xffffff, false);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
		return;
	}

	if (drawFunc_ != nullptr)
	{
		drawFunc_(pos_);
		return;
	}
	
	if (gHandle_ == -1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
		DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, color_, true);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	}
	else
	{
		DrawRotaGraph(pos_.x - size_.x / 2, pos_.y - size_.y / 2, 1.0, 0.0, gHandle_, true);
	}
}

void Canvas::Update()
{
	if (!isActive_)
	{
		return;
	}

	for (auto& uiStat : UIList_)
	{
		if (uiStat.ui->Update())
		{
			break;
		}
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

void Canvas::ClearUI()
{
	for (auto& ui : UIList_)
	{
		delete(ui.ui);
	}
	UIList_.erase(UIList_.begin(), UIList_.end());
	UIList_.shrink_to_fit();
}

void Canvas::SetActive(bool active)
{
	isActive_ = active;
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
