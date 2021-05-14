#pragma once
#include "Player.h"
#include "PlayerType.h"
#include <vector>
#include <memory>

constexpr int MAX_COST = 16;

#define lpPlayerMng PlayerMng::GetInstance()

class PlayerMng
{
public:
	static PlayerMng& GetInstance()
	{
		static PlayerMng s_Instance;
		return s_Instance;
	}
	~PlayerMng() = default;
	void Init();
	void Update(float deltaTime);
	void Update(float deltaTime,Vec2Float pos);
	void Draw(void);
	bool Spawner(PlayerUnit id,Vec2Float pos);
	void Skill(void) {};
	int GetCost(void);
	void SetCost(int cost);
private:
	PlayerMng();
	std::vector<std::shared_ptr<Player>> unitList_;
	int cost;		//所持コスト保存用
};

