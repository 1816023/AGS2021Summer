#pragma once
#include "VECTOR2.h"
#define lpCollison Collision::GetInstance()

class Collision
{
public:
	~Collision();
	static Collision& GetInstance()
	{
		static Collision s_Instance;
		return s_Instance;
	}
	const bool CvC(Vec2Float pos, float r, Vec2Float pos2, float r2);	//�~�Ɖ~�i�������Ă���ꍇtrue�j
private:
	Collision();
};

