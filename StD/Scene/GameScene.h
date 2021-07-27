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
	void Draw()override;
	void DrawUI()override;
	void MenuDraw(VECTOR2& m_pos);
	void UnitCreateFunc(void);
	void UnitAccessFunc(void);
	void BulletControler(float deltaTime);
	//デバッグ
	std::unique_ptr<Map> map;
	std::unique_ptr<PlayerMng> playerMng_;
	std::unique_ptr<EnemyManager> enemyMng_;
	// 現在はここにMapに移す予定
	std::vector<std::shared_ptr<EnemySpawner>>enemySpawner_;	// 敵生成クラス

	std::unique_ptr<ShotMng> shotMng_;	//弾管理クラス

	PlayerUnit selectUnitId;
	int cnt;	
	std::shared_ptr<Player> accessData;	//クリック時に取得したユニットのデータ
	bool waitFlag;	

	bool resultFlag;
};