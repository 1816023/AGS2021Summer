#pragma once
#include "Player.h"
#include "PlayerType.h"
#include <vector>
#include <map>
#include <memory>

constexpr int MAX_COST = 16;

using UnitList = std::vector<std::shared_ptr<Player>>;

class ShotMng;
class PlayerMng
{
public:
	PlayerMng();
	~PlayerMng();
	void Init();
	void Update(float deltaTime,std::shared_ptr<Unit> shooter);
	void Draw(void);
	bool Spawner(PlayerUnit id,Vec2Float pos);
	void Skill(void) {};
	UnitList GetUnitList(void);	//プレイヤー側のUnitリストの取得
	std::map<PlayerUnit, UnitData> GetPlayerData(void);
	int GetCost(void);
	void SetCost(int cost);
	float SpeedDelay(void);
	std::shared_ptr<Player> GetUnitData(Vec2Float pos);
private:
	void SkillCtl(std::shared_ptr<Unit> shooter);
	UnitList unitList_;
	std::map<PlayerUnit,UnitData> playerData;
	int cost;		//所持コスト保存用
};

