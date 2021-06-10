#pragma once
#include "Player.h"
#include "PlayerType.h"
#include <vector>
#include <memory>

constexpr int MAX_COST = 16;

class ShotMng;
class PlayerMng
{
public:
	PlayerMng();
	~PlayerMng();
	void Init();
	void Update(float deltaTime);
	void Update(float deltaTime,Vec2Float pos);
	void Draw(void);
	bool Spawner(PlayerUnit id,Vec2Float pos);
	void Skill(void) {};
	int GetCost(void);
	void SetCost(int cost);
	float SpeedDelay(void);
private:
	void SkillCtl(void);
	std::unique_ptr<ShotMng> shotMng_;
	std::vector<std::shared_ptr<Player>> unitList_;
	int cost;		//所持コスト保存用
};

