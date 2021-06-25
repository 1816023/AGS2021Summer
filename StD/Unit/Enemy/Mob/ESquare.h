#pragma once
#include "../Enemy.h"
class ESquare : public Enemy
{
public:
	ESquare();
	ESquare(MapInfo& mapInfo);
	~ESquare();

	// �X�V
	void Update(float deltaTime)override;
	// �`��
	void Draw()override;
	// �N���[���쐻
	Enemy* CreateClone()override;
private:
	// --- �e��X�V���� ---
	using Func_t = void (ESquare::*)(float);
	Func_t updater_;
	// ��������
	void StartUpdate(float deltaTime);
	// �ړ��Ȃ�
	void RunUpdate(float deltaTime);
	// ���񂾂Ƃ�
	void deathUpdate(float deltaTime);
	// --------------------
};

