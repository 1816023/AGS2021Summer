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

class Unit;

class ShotMng
{
public:
	ShotMng();
	~ShotMng();
	void Init(void);				//初期化
	void Update(float deltaTime);	//更新
	void Draw(void);				//弾の描画
	void AddBullet(std::shared_ptr<Unit> ptr, Vec2Float pos);			//Unitから発射される弾の作成
	void BulletMove(std::shared_ptr<Unit> ptr/*射出点ユニット*/,Vec2Float pos/*射出点座標*/);	//弾の移動
	bool isRange(Vec2Float unitPos,Vec2Float bulletPos,float unitSize,float bulletSize);
	bool isHitBvE(Vec2Float bulletPos, float bulletSize, Vec2Float unitPos, Vec2Float unitSize);

	const std::shared_ptr<Unit>& GetShooterPtr()
	{
		return shooterPtr_;
	}
private:
	std::map<std::shared_ptr<Unit>, std::list<std::pair<Vec2Float, Vec2Float>>> shotList_;	//弾管理用 (リストのfirstには射出点secondには弾の現在座標が入る)
	std::map<std::shared_ptr<Unit>, int> shotSpan_;	//発射間隔管理用
	std::shared_ptr<Unit> shooterPtr_;
};

