#pragma once
#include "Player.h"
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
	bool Spawner(PlayerUnit id);
private:
	PlayerMng();
	void Init();
	std::vector<std::unique_ptr<Player>> unitList_;
};

