#pragma once
#include "Enemy.h"
class ECircle : public Enemy
{
public:
	ECircle(Vec2Float pos);
	~ECircle();

	void Update(float deltaTime)override;
	void Draw()override;


};

