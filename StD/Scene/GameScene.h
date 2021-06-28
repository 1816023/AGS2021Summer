#pragma once
#include "BaseScene.h"
#include "../Map/Map.h"

class ShotMng;
class PlayerMng;
class EnemyManager;
class EnemySpawner;
class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	unique_Base Update(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::GAME; }
private:
	void Draw()override;
	void DrawUI()override;
	void MenuDraw(VECTOR2& m_pos);
	void BulletControler(void);
	//�f�o�b�O
	std::unique_ptr<Map> map;
	std::unique_ptr<PlayerMng> playerMng_;
	std::unique_ptr<EnemyManager> enemyMng_;

	// ���݂͂�����Map�Ɉڂ��\��
	std::vector<std::shared_ptr<EnemySpawner>>enemySpawner_;	// �G�����N���X

	std::unique_ptr<ShotMng> shotMng_;	//�e�Ǘ��N���X
};

