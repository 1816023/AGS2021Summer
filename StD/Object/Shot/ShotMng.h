#pragma once
#include "Shot.h"
#include "../../Geometry.h"
#include "../../VECTOR2.h"
#include <memory>
#include <vector>
#define lpShotMng ShotMng::GetInstance()

class Player;

struct BulletStatus
{
	std::shared_ptr<Player> player;
	Vec2Float pos;
};

class ShotMng :
	public Shot
{
public:
	static ShotMng& GetInstance()
	{
		static ShotMng s_Instance;
		return s_Instance;
	}
	~ShotMng();
	void Init(void);				//初期化
	void Update(float deltaTime);	//更新
	void Draw(void);				//弾の描画
	void AddBullet(std::shared_ptr<Player> unit);			//Unitから発射される弾の作成
	void BulletMove(void);
private:
	ShotMng();
	std::vector<BulletStatus> shotList_;
};

