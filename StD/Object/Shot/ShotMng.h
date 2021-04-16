#pragma once
#include "Shot.h"
#include "../../Geometry.h"
#include <memory>
#include <vector>
#define lpShotMng ShotMng::GetInstance()

class Player;

struct BulletStatus
{
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
private:
	ShotMng();
	std::vector<std::shared_ptr<Player>> shotList_;
};

