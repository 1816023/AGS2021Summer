#include "ECircle.h"
#include "../../Mng/ImageMng.h"
#include "../../Map/Map.h"

ECircle::ECircle() : Enemy()
{
	
}

ECircle::ECircle(MapInfo& mapInfo):Enemy(mapInfo)
{
	updater_ = &ECircle::StartUpdate;
	state_.life = MID_HP;
	dirVec = { 0,0 };
	nowMove_ = { 0,0 };
	rootIdx_ = 0;
	mapChipSize = mapInfo.chipSize;
	mapSize = mapInfo.mapSize;
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
	DrawRotaGraph(state_.pos.x, state_.pos.y, scale_, 0.0f, IMAGE_ID(L"data/image/circle.png"), true);
}

Enemy* ECircle::CreateClone()
{
	ECircle* enemy = new ECircle();
	enemy->updater_ = updater_;
	enemy->dirVec = dirVec;
	enemy->nowMove_ = nowMove_;
	enemy->rootIdx_ = rootIdx_;
	enemy->mapChipSize = mapChipSize;
	enemy->mapSize = mapSize;
	enemy->scale_ = scale_;
	enemy->state_ = state_;
	return enemy;
}

void ECircle::StartUpdate(float deltaTime)
{
	SearchRoot(deltaTime);
	updater_ = &ECircle::RunUpdate;
}

void ECircle::RunUpdate(float deltaTime)
{
	Move(deltaTime);
	if (state_.life <= 0)
	{
		state_.isDead = true;
	}
}

void ECircle::Move(float deltaTime)
{
	// 移動値計算
	auto move = dirVec * 10.0f * deltaTime;
	// 移動終了かどうか(１チップ)
	if (std::abs(nowMove_.x + move.x) >= mapChipSize.x
		|| std::abs(nowMove_.y + move.y) >= mapChipSize.y)
	{
		// 移動補正
		state_.pos -= nowMove_;
		state_.pos = state_.pos.Round();
		state_.pos = state_.pos + (Vec2Float( mapChipSize.x, mapChipSize.y) * dirVec).Round();
		// 移動値初期化
		nowMove_ = { 0,0 };
		move = { 0,0 };
		// 方向設定
		SearchRoot(deltaTime);
	}
	// 移動値加算
	state_.pos += move;
	nowMove_ += move;
}

void ECircle::SearchRoot(float deltaTime)
{
	dirVec = { 0,0 };
	if (root_.size() <= rootIdx_)
	{
		rootIdx_ = 0;
	}
	switch (root_[rootIdx_])
	{
	case RootDir::UP:
		dirVec = { 0,-1 };
		break;
	case RootDir::DOWN:
		dirVec = { 0,1 };
		break;
	case RootDir::LEFT:
		dirVec = { -1,0 };
		break;
	case RootDir::RIGHT:
		dirVec = { 1,0 };
		break;
	default:
		break;
	}
	rootIdx_++;
}

void ECircle::deathUpdate(float deltaTime)
{
}

