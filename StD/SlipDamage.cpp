#include "SlipDamage.h"
#include "MouseController.h"

SlipDamage::SlipDamage(VECTOR2 pos)
{
	this->pos = pos;
}

SlipDamage::~SlipDamage()
{
}

void SlipDamage::Update()
{
}

void SlipDamage::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1, 0, slipDamage, false);
}
