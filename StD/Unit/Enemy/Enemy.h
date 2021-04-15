#pragma once
#include "../Unit.h"

class Enemy : public Unit
{
public:
	Enemy();
	~Enemy();
	void Update(float deltaTime)override;
	void Draw()override;
private:

};

