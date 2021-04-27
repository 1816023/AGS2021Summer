#pragma once
#include "../../Geometry.h"
#include "../../VECTOR2.h"
#include <memory>
#include <vector>
#include <string>
#include <list>
#include <map>

constexpr auto BASE_SPAN = 30;	//๎beฌ

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
	void Init(void);				//๚ป
	void Update(float deltaTime);	//XV
	void Draw(void);				//eฬ`ๆ
	void AddBullet(Player* ptr, Vec2Float pos);			//Unitฉ็ญหณ๊้eฬ์ฌ
	void BulletMove(Player* ptr);	//eฬฺฎ
private:
	ShotMng();
	std::map<Player*, std::list<Vec2Float>> shotList_;	//eวp
	std::map<Player*, int> shotSpan_;	//ญหิuวp
};

