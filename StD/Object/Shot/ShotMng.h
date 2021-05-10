#pragma once
#include "../../Geometry.h"
#include "../../VECTOR2.h"
#include <memory>
#include <vector>
#include <string>
#include <list>
#include <map>

constexpr auto BASE_SPAN = 15;	//��b�e�Ԋu
constexpr auto BASE_DIST = 150;	//��b�˒�
constexpr auto BASE_SIZE = 5;	//�e�̔��a

#define lpShotMng ShotMng::GetInstance()

class Unit;

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
	void AddBullet(std::shared_ptr<Unit> ptr, Vec2Float pos);			//Unit���甭�˂����e�̍쐬
	void BulletMove(std::shared_ptr<Unit> ptr,Vec2Float pos);			//�e�̈ړ�
	bool isRange(Vec2Float unitPos,Vec2Float bulletPos,float unitSize,float bulletSize);
	bool isHitBvE(Vec2Float bulletPos, float bulletSize, Vec2Float unitPos, Vec2Float unitSize);		//�e�ƓG�̓����蔻��
private:
	ShotMng();
	std::map<std::shared_ptr<Unit>, std::list<std::pair<Vec2Float, Vec2Float>>> shotList_;	//�e�Ǘ��p (���X�g��first�ɂ͎ˏo�_second�ɂ͒e�̌��ݍ��W������)
	std::map<std::shared_ptr<Unit>, int> shotSpan_;	//���ˊԊu�Ǘ��p
};

