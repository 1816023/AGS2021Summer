#pragma once
#include "../Unit.h"

class Enemy : public Unit
{
public:
	Enemy(Vec2Float pos);
	~Enemy();
	virtual void Update(float deltaTime)override;
	virtual void Draw()override;
private:

};

