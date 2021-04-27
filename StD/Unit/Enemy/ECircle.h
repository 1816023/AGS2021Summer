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
	int rootType;	// ���[�g�̎��
	int rootIdx_;	// ���[�g�̃C���f�b�N�X
	Vec2Float dirVec;		// �ړ������̃x�N�g��
	Vec2Float nowMove_;		// �O�񌈒肵�Ă���̈ړ��l
	VECTOR2 mapChipSize;	// �}�b�v�̃`�b�v�T�C�Y
	VECTOR2 mapSize;		// �}�b�v�̃`�b�v��
	
	// --- �e��X�V���� ---
	using Func_t = void (ECircle::*)(float);
	Func_t updater_;
	// �ړ��Ȃ�
	void RunUpdate(float deltaTime);
	// �ړ������̌��������
	void SearchUpdate(float deltaTime);
	// ���񂾂Ƃ�
	void deathUpdate(float deltaTime);
	// --------------------

	// �ړ�����
	void Move(float deltaTime);
};

