#pragma once
#include "../Unit.h"
#include "../../VECTOR2.h"
#include "EnemyType.h"
#include <vector>

// パラメータ定数
// HP
#define LOW_HP 60		
#define MID_HP 120
#define HIGH_HP 180
// 攻撃力
#define LOW_ATK 1
#define MID_ATK 2
#define HIGH_ATK 3
// 射程
#define LOW_DIST 10
#define MID_DIST 20
#define HIGH_DIST 30
// 速度
#define LOW_SPEED 5
#define MID_SPEED 10
#define HIGH_SPEED 15

// 大きさ
#define E_SIZE_X 64
#define E_SIZE_Y 64

// マップ情報(必要なもの)
struct MapInfo
{
	VECTOR2 chipSize;	// 1チップの大きさ
	VECTOR2 mapSize;	// マップのチップ数
};



class Map;
class Enemy : public Unit
{
public:
	Enemy();
	Enemy(MapInfo& mapInfo);
	virtual ~Enemy();
	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual Enemy* CreateClone() = 0;
	unsigned int GetHP();
	Vec2Float GetPosition();
	void SetPosition(Vec2Float pos);
	void SetRoot(std::vector<RootDir>& root);
	bool IsDeath();
	const float GetSpeed();
	void SetSpeed(float speed);
protected:
	struct EnemyInfo
	{
		std::vector<RootDir> root;
		float scale;
		VECTOR2 mapChipSize;	// マップのチップサイズ
		VECTOR2 mapSize;		// マップのチップ数
		int rootIdx;	// ルートのインデックス
		Vec2Float dirVec;		// 移動方向のベクトル
		Vec2Float nowMove;		// 前回決定してからの移動値
		float speed;
	};
	// 移動処理
	void Move(float deltaTime);
	// 移動方向の決定をする
	void SearchRoot(float deltaTime);
	
	EnemyInfo enemyInfo_;
};

