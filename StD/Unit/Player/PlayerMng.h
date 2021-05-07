#pragma once
#include "Player.h"
#include "PlayerType.h"
#include <vector>
#include <memory>

#define lpPlayerMng PlayerMng::GetInstance()

class PlayerMng :
	public Player
{
public:
	static PlayerMng& GetInstance()
	{
		static PlayerMng s_Instance;
		return s_Instance;
	}
	~PlayerMng() = default;
	void Update(float deltaTime);
	void Update(float deltaTime,Vec2Float pos);
	void Draw(void);
	bool Spawner(PlayerUnit id,Vec2Float pos);
	void Skill(void) {};

	Vec2Float GetPos(void)override;
private:
	PlayerMng();
	void Init();
	std::vector<std::shared_ptr<Player>> unitList_;
};

