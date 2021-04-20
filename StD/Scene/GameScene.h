#pragma once
#include "BaseScene.h"
#include "../Map/Map.h"
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
	//�f�o�b�O
	std::unique_ptr<Map> map;

	// ���݂͂�����Map�Ɉڂ��\��
	std::vector<std::shared_ptr<EnemySpawner>>enemySpawner_;	// �G�����N���X
};

