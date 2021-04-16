#pragma once
#include "Player.h"
#include "PlayerType.h"
#include <vector>
#include <memory>
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
	void Updata(float deltaTime);
	bool Spawner(PlayerUnit id);
private:
	PlayerMng();
	void Init();
	std::vector<std::shared_ptr<Player>> unitList_;
};

