#pragma once
#include <DxLib.h>

// UnitΜXe[^X(€Κͺ)
struct UnitStat
{
	unsigned int power;		// UΝ
	unsigned int life;		// ΜΝ
	float atkSpeed;			// U¬x
	float atkDist;			// Λφ
};

// UnitξκNX
class Unit
{
public:
	Unit() = default;
	virtual ~Unit() = default;
	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	UnitStat state_;
};

