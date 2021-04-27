#pragma once
#include "../../Geometry.h"
#include "../../VECTOR2.h"
#include <memory>
#include <vector>
#include <string>
#include <list>
#include <map>

constexpr auto BASE_SPAN = 30;	//Šî‘b’e‘¬

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
	void Init(void);				//‰Šú‰»
	void Update(float deltaTime);	//XV
	void Draw(void);				//’e‚Ì•`‰æ
	void AddBullet(Player* ptr, Vec2Float pos);			//Unit‚©‚ç”­Ë‚³‚ê‚é’e‚Ìì¬
	void BulletMove(Player* ptr);	//’e‚ÌˆÚ“®
private:
	ShotMng();
	std::map<Player*, std::list<Vec2Float>> shotList_;	//’eŠÇ——p
	std::map<Player*, int> shotSpan_;	//”­ËŠÔŠuŠÇ——p
};

