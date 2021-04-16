#pragma once
#include "Shot.h"
#include "../../Geometry.h"
#include "../../VECTOR2.h"
#include <memory>
#include <vector>
#define lpShotMng ShotMng::GetInstance()

class Player;

struct BulletStatus
{
	std::shared_ptr<Player> player;
	Vec2Float pos;
};

class ShotMng :
	public Shot
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
	void AddBullet(std::shared_ptr<Player> unit);			//Unit���甭�˂����e�̍쐬
	void BulletMove(void);
private:
	ShotMng();
	std::vector<BulletStatus> shotList_;
};

