#pragma once
#include"BaseScene.h"
#include<string>
#include<list>
#include "../GUI/Button/Button.h"
#include "../Unit/Enemy/EnemyType.h"
#include "../GUI/PullDown/PullDown.h"
#include "../Map/Simple.h"
struct EnemyListState {
	EnemyType type;
	double time;
	int rootID;
	int spawner;
	int wave;
};

class GameMapSellectScene :
	public BaseScene
{
public:
	GameMapSellectScene();
	~GameMapSellectScene();
	unique_Base Update(unique_Base own);
	void Draw();
	void DrawUI();
	SCENE_ID GetScnID(void);
private:
	std::list<EnemyListState>LoadEnemyData(std::string path);
	std::list<EnemyListState>enemyList_;
	std::list<Button*>button_;
	PullDown*pullDown_;
	std::unique_ptr<Simple>map_;
	bool CheckData(std::string);
	unsigned int transitionFlag_;
};

