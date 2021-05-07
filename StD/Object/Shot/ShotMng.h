#pragma once
#include "../../Geometry.h"
#include "../../VECTOR2.h"
#include <memory>
#include <vector>
#include <string>
#include <list>
#include <map>

constexpr auto BASE_SPAN = 15;	//基礎弾間隔
constexpr auto BASE_DIST = 150;	//基礎射程
constexpr auto BASE_SIZE = 5;	//弾の半径

#define lpShotMng ShotMng::GetInstance()

class Player;

class ShotMng
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
	void AddBullet(std::shared_ptr<Player> ptr, Vec2Float pos);			//Unitから発射される弾の作成
	void BulletMove(std::shared_ptr<Player> ptr,Vec2Float pos);			//弾の移動
	bool isRange(Vec2Float unitPos,Vec2Float bulletPos,float unitSize,float bulletSize);
	bool isHitBvE(Vec2Float bulletPos);		//弾と敵の当たり判定
private:
	ShotMng();
	std::map<std::shared_ptr<Player>, std::list<std::pair<Vec2Float, Vec2Float>>> shotList_;	//弾管理用 (リストのfirstには射出点secondには弾の現在座標が入る)
	std::map<std::shared_ptr<Player>, int> shotSpan_;	//発射間隔管理用
};

