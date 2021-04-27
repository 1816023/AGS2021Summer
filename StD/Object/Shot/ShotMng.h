#pragma once
#include "../../Geometry.h"
#include "../../VECTOR2.h"
#include <memory>
#include <vector>
#include <string>
#include <list>
#include <map>

constexpr auto BASE_SPAN = 30;	//��b�e��

#define lpShotMng ShotMng::GetInstance()

class Player;

class ShotMng
{
public:
	static ShotMng& GetInstance()
	{
		static ShotMng s_Instance;
		return s_Instance;
	}
	~ShotMng();
	void Init(void);				//������
	void Update(float deltaTime);	//�X�V
	void Draw(void);				//�e�̕`��
	void AddBullet(Player* ptr, Vec2Float pos);			//Unit���甭�˂����e�̍쐬
	void BulletMove(Player* ptr);	//�e�̈ړ�
private:
	ShotMng();
	std::map<Player*, std::list<Vec2Float>> shotList_;	//�e�Ǘ��p
	std::map<Player*, int> shotSpan_;	//���ˊԊu�Ǘ��p
};

