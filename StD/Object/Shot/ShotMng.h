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
	void AddBullet(std::shared_ptr<Player> ptr, Vec2Float pos);			//Unit���甭�˂����e�̍쐬
	void BulletMove(std::shared_ptr<Player> ptr);	//�e�̈ړ�
	bool isRange(Vec2Float unitPos,Vec2Float bulletPos,float unitSize,float bulletSize);
private:
	ShotMng();
	std::map<std::shared_ptr<Player>, std::list<std::pair<Vec2Float, Vec2Float>>> shotList_;	//�e�Ǘ��p (���X�g��first�ɂ͎ˏo�_second�ɂ͒e�̌��ݍ��W������)
	std::map<std::shared_ptr<Player>, int> shotSpan_;	//���ˊԊu�Ǘ��p
};

