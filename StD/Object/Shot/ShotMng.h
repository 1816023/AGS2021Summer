#pragma once
#include "../../Geometry.h"
#include "../../VECTOR2.h"
#include <memory>
#include <vector>
#include <string>
#include <list>
#include <map>

constexpr auto BASE_SPAN = 30;	//��b�e�Ԋu
constexpr auto BASE_DIST = 150;	//��b�˒�
constexpr auto BASE_SIZE = 5;	//�e�̔��a

class Unit;

class ShotMng
{
public:
	ShotMng();
	~ShotMng();
	void Init(void);				//������
	void Update(float deltaTime);	//�X�V
	void Draw(void);				//�e�̕`��
	void AddBullet(std::shared_ptr<Unit> ptr, std::shared_ptr<Unit> target/*�ڕW�̃|�C���^*/);			//Unit���甭�˂����e�̍쐬
	std::shared_ptr<Unit> BulletMove(std::shared_ptr<Unit> ptr/*�ˏo�_���j�b�g*/, std::shared_ptr<Unit> target/*�ˏo�_���W*/);	//�e�̈ړ�
	void AreaAttackCtl(std::vector<std::shared_ptr<Unit>> unitList);
	bool isRange(Vec2Float unitPos/*����Ώ�*/,Vec2Float shooterPos/*�ˏo�ʒu*/,float unitSize/*�Ώۂ̃T�C�Y*/,float rangeSize/*�͈�*/);
	bool isCoolTime(std::shared_ptr<Unit> ptr);
	bool isHitBvE(Vec2Float bulletPos, float bulletSize, Vec2Float unitPos, Vec2Float unitSize);

	const std::shared_ptr<Unit>& GetShooterPtr()
	{
		return shooterPtr_;
	}
private:
	std::map<std::shared_ptr<Unit>, std::list<std::pair<Vec2Float, std::shared_ptr<Unit>>>> shotList_;	//�e�Ǘ��p (���X�g��first�ɂ͎ˏo�_second�ɂ͖ڕW�Ώۂ�����)
	std::map<std::shared_ptr<Unit>, int> shotSpan_;	//���ˊԊu�Ǘ��p
	std::shared_ptr<Unit> shooterPtr_;
};

