#pragma once
#include "../Unit.h"
#include "../../VECTOR2.h"

class Enemy : public Unit
{
public:
	Enemy();
	~Enemy();
	virtual void Update(float deltaTime)override;
	virtual void Draw()override;
	virtual void SetPosition(Vec2Float pos) = 0;
private:

};

