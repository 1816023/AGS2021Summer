#pragma once
#include "../Enemy.h"

// �~�`�̓G
class ECircle : public Enemy
{
public:
	ECircle();
	ECircle(MapInfo& mapInfo);
	~ECircle();

	// �X�V
	void Update(float deltaTime)override;
	// �`��
	void Draw()override;
	// �N���[���쐻
	Enemy* CreateClone()override;
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

