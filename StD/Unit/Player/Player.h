#pragma once
#include "../Unit.h"
enum class PlayerUnit
{
	YELLOW,
	GREEN,
	BLUE,
	PINK,
	MAX
};

class Player: public Unit
{
public:
	Player() = default;
	~Player() = default;
	void Init();
	void Update(float deltaTime)override;
	void Draw()override;
	bool Spawner(PlayerUnit id);
private:
};

