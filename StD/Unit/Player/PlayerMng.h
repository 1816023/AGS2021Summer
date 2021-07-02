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
	UnitList GetUnitList(void);	//�v���C���[����Unit���X�g�̎擾
	std::map<PlayerUnit, int> GetPlayerData(void);
	int GetCost(void);
	void SetCost(int cost);
	float SpeedDelay(void);
private:
	void SkillCtl(std::shared_ptr<Unit> shooter);
	UnitList unitList_;
	std::map<PlayerUnit,int> playerData;
	int cost;		//�����R�X�g�ۑ��p
};

