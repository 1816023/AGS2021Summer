#pragma once
#include "Enemy.h"
class ECircle : public Enemy
{
public:
	ECircle();
	~ECircle();

	void Update(float deltaTime)override;
	void Draw()override;
};

