#pragma once
#include <string>
#include "BaseScene.h"
#include "../Map/Map.h"
#include "../Unit/Player/PlayerType.h"

struct MenuState
{
	std::string name;
	int imageId;
	Vec2Float pos;
};
class ShotMng;
class Player;
class PlayerMng;
class EnemyManager;
class EnemySpawner;
class GameScene :
	public BaseScene
{
public:
	GameScene();
	GameScene(std::string mapName);
	~GameScene();

	unique_Base Update(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::GAME; }
private:
	void Init();
	void Draw()override;
	void DrawUI()override;
	void MenuDraw(VECTOR2& m_pos);
	void UnitCreateFunc(void);
	void UnitAccessFunc(void);
	//�f�o�b�O
	std::unique_ptr<Map> map_;
	std::shared_ptr<PlayerMng> playerMng_;
	std::shared_ptr<EnemyManager> enemyMng_;
	std::vector<std::shared_ptr<EnemySpawner>>enemySpawner_;	// �G�����N���X

	std::unique_ptr<ShotMng> shotMng_;	//�e�Ǘ��N���X

	PlayerUnit selectUnitId;
	int cnt;	
	std::shared_ptr<Player> accessData;	//�N���b�N���Ɏ擾�������j�b�g�̃f�[�^
	bool waitFlag;	

	bool resultFlag;
};