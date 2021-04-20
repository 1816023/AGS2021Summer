#include "ECircle.h"

ECircle::ECircle() : Enemy()
{
	updater = &ECircle::RunUpdate;
}

ECircle::~ECircle()
{
}

void ECircle::Update(float deltaTime)
{
	(this->*updater)(deltaTime);
}

void ECircle::Draw()
{
	DrawCircle(state_.pos.x, state_.pos.y, 5, 0xff0000);
}

Enemy* ECircle::CreateClone()
{
	return new ECircle();
}

void ECircle::RunUpdate(float deltaTime)
{
	state_.pos.y += 5 * deltaTime;
}

void ECircle::deathUpdate(float deltaTime)
{
}

