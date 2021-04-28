#pragma once
#include "Enemy.h"


class ECircle : public Enemy
{
public:
	ECircle();
	ECircle(MapInfo& mapInfo);
	~ECircle();

	void Update(float deltaTime)override;
	void Draw()override;
	Enemy* CreateClone();
private:	
	// --- �e��X�V���� ---
	using Func_t = void (ECircle::*)(float);
	Func_t updater_;
	// ��������
	void StartUpdate(float deltaTime);
	// �ړ��Ȃ�
	void RunUpdate(float deltaTime);
	
	// ���񂾂Ƃ�
	void deathUpdate(float deltaTime);
	// --------------------
};

