#pragma once
#include "../../Geometry.h"
#include "../../VECTOR2.h"
#include <memory>
#include <vector>
#include <string>
#include <list>
#include <map>

constexpr auto BASE_SPAN = 15;	//Šî‘b’eŠÔŠu
constexpr auto BASE_DIST = 150;	//Šî‘bË’ö
constexpr auto BASE_SIZE = 5;	//’e‚Ì”¼Œa

#define lpShotMng ShotMng::GetInstance()

class Unit;

class ShotMng
{
public:
	static ShotMng& GetInstance()
	{
		static ShotMng s_Instance;
		return s_Instance;
	}
	~ShotMng();
	void Init(void);				//‰Šú‰»
	void Update(float deltaTime);	//XV
	void Draw(void);				//’e‚Ì•`‰æ
	void AddBullet(std::shared_ptr<Unit> ptr, Vec2Float pos);			//Unit‚©‚ç”­Ë‚³‚ê‚é’e‚Ìì¬
	void BulletMove(std::shared_ptr<Unit> ptr,Vec2Float pos);			//’e‚ÌˆÚ“®
	bool isRange(Vec2Float unitPos,Vec2Float bulletPos,float unitSize,float bulletSize);
	bool isHitBvE(Vec2Float bulletPos, float bulletSize, Vec2Float unitPos, Vec2Float unitSize);		//’e‚Æ“G‚Ì“–‚½‚è”»’è
private:
	ShotMng();
	std::map<std::shared_ptr<Unit>, std::list<std::pair<Vec2Float, Vec2Float>>> shotList_;	//’eŠÇ——p (ƒŠƒXƒg‚Ìfirst‚É‚ÍËo“_second‚É‚Í’e‚ÌŒ»İÀ•W‚ª“ü‚é)
	std::map<std::shared_ptr<Unit>, int> shotSpan_;	//”­ËŠÔŠuŠÇ——p
};

