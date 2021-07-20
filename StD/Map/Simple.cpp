#include "Simple.h"
#include<DxLib.h>
Simple::Simple()
{
	MakeScreen(DEFAULT_SCREEN_SIZE_X, DEFAULT_SCREEN_SIZE_Y, 1);
}

Simple::~Simple()
{
}

int Simple::Update()
{
	return 0;
}

void Simple::Draw()
{
	auto defScreen = GetDrawScreen();

	Map::Draw();
	const VECTOR2 rectSize=state_.chipSize_*state_.mapSize_;
	DrawRectExtendGraph(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0, 0, rectSize.x, rectSize.y, screen_, true);
}

void Simple::SetMap(std::string path)
{
	LoadMap(path);
	
}

void Simple::SetSize(VECTOR2 size)
{
	size_ = size;
}
