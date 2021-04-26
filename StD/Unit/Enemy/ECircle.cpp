#include "ECircle.h"
#include "../../Mng/ImageMng.h"
#include "../../Map/Map.h"

ECircle::ECircle() : Enemy()
{
	
}

ECircle::ECircle(Map& map):Enemy(map)
{
	updater_ = &ECircle::SearchUpdate;
	move_ = { 0,0 };
	nowMove_ = { 0,0 };
	rootIdx_ = 0;
	mapChipSize = map.GetChipSize();
	mapSize = map.GetMapSize();
}

ECircle::~ECircle()
{
}

void ECircle::Update(float deltaTime)
{
	(this->*updater_)(deltaTime);
}

void ECircle::Draw()
{
	DrawRotaGraph(state_.pos.x, state_.pos.y, 1.0f, 0.0f, IMAGE_ID(L"data/image/circle.png"), true);
}

Enemy* ECircle::CreateClone()
{
	ECircle* enemy = new ECircle();
	enemy->updater_ = updater_;
	enemy->move_ = move_;
	enemy->nowMove_ = nowMove_;
	enemy->rootIdx_ = rootIdx_;
	enemy->mapChipSize = mapChipSize;
	enemy->mapSize = mapSize;
	return enemy;
}

void ECircle::RunUpdate(float deltaTime)
{
	if (std::abs(nowMove_.x) >= mapChipSize.x || std::abs(nowMove_.y) >= mapChipSize.y)
	{
		updater_ = &ECircle::SearchUpdate;
		map_->GetMapChip(state_.pos);
		nowMove_ = { 0,0 };
	}
	auto move = move_ * 4.0f * deltaTime;
	state_.pos += move;
	nowMove_ += move;
}

void ECircle::SearchUpdate(float deltaTime)
{
	move_ = { 0,0 };
	if (root_.size() <= rootIdx_)
	{
		rootIdx_ = 0;
	}
	switch (root_[rootIdx_])
	{
	case RootDir::UP:
		move_ = { 0,-1 };
		break;
	case RootDir::DOWN:
		move_ = { 0,1 };
		break;
	case RootDir::LEFT:
		move_ = { -1,0 };
		break;
	case RootDir::RIGHT:
		move_ = { 1,0 };
		break;
	default:
		break;
	}
	rootIdx_++;
	updater_ = &ECircle::RunUpdate;
}

void ECircle::deathUpdate(float deltaTime)
{
}

