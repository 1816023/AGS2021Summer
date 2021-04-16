#include "SlipDamage.h"
#include "MouseController.h"

SlipDamage::SlipDamage()
{
}

SlipDamage::~SlipDamage()
{
}

void SlipDamage::Update()
{
	Draw();
}

void SlipDamage::Draw()
{
	DrawGraph(lpMouseController.GetPos().x, lpMouseController.GetPos().y, slipDamage, false);
}
