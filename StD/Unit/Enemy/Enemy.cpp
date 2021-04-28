#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(MapInfo& mapInfo)
{
	// x方向にスケーリング
	enemyInfo_.scale = E_SIZE_X / mapInfo.chipSize.x;
	state_.isDead = false;
	enemyInfo_.mapChipSize = mapInfo.chipSize;
	enemyInfo_.mapSize = mapInfo.mapSize;
}

Enemy::~Enemy()
{
}
void Enemy::Update(float deltaTime)
{
}

void Enemy::Draw()
{
}

unsigned int Enemy::GetHP()
{
	return state_.life;
}

Vec2Float Enemy::GetPosition()
{
	return state_.pos;
}

void Enemy::SetPosition(Vec2Float pos)
{
	state_.pos = pos;
}

void Enemy::SetRoot(std::vector<RootDir>& root)
{
	enemyInfo_.root = root;
}

bool Enemy::IsDeath()
{
	return state_.isDead;
}

const float Enemy::GetSpeed()
{
	return enemyInfo_.speed;
}

void Enemy::SetSpeed(float speed)
{
	enemyInfo_.speed = speed;
}

void Enemy::Move(float deltaTime)
{
	// 移動値計算
	auto move = enemyInfo_.dirVec * enemyInfo_.speed * deltaTime;
	// 移動終了かどうか(１チップ)
	if (std::abs(enemyInfo_.nowMove.x + move.x) >= enemyInfo_.mapChipSize.x
		|| std::abs(enemyInfo_.nowMove.y + move.y) >= enemyInfo_.mapChipSize.y)
	{
		// 移動補正
		state_.pos = (state_.pos - enemyInfo_.nowMove).Round();
		state_.pos = state_.pos + (Vec2Float(enemyInfo_.mapChipSize.x, enemyInfo_.mapChipSize.y) * enemyInfo_.dirVec).Round();
		// 移動値初期化
		enemyInfo_.nowMove = { 0,0 };
		move = { 0,0 };
		// 方向設定
		SearchRoot(deltaTime);
	}
	// 移動値加算
	state_.pos += move;
	enemyInfo_.nowMove += move;
}

void Enemy::SearchRoot(float deltaTime)
{
	enemyInfo_.dirVec = { 0,0 };
	if (enemyInfo_.root.size() <= enemyInfo_.rootIdx)
	{
		enemyInfo_.rootIdx = 0;
	}
	switch (enemyInfo_.root[enemyInfo_.rootIdx])
	{
	case RootDir::UP:
		enemyInfo_.dirVec = { 0,-1 };
		break;
	case RootDir::DOWN:
		enemyInfo_.dirVec = { 0,1 };
		break;
	case RootDir::LEFT:
		enemyInfo_.dirVec = { -1,0 };
		break;
	case RootDir::RIGHT:
		enemyInfo_.dirVec = { 1,0 };
		break;
	default:
		break;
	}
	enemyInfo_.rootIdx++;
}
