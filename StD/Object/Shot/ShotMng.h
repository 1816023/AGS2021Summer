#pragma once
#include "Shot.h"
#include "../../Geometry.h"
#include <memory>
#include <vector>
#define lpShotMng ShotMng::GetInstance()

class Player;

struct BulletStatus
{
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
private:
	ShotMng();
	std::vector<std::shared_ptr<Player>> shotList_;
};

