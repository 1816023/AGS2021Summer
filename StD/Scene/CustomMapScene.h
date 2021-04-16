#pragma once
#include "BaseScene.h"
#include "../Map/Custom.h"
#include <functional>
#include <map>

enum class CustomState {
	SET_STATE,			// マップの幅や高さを設定する状態
	MAP_CUSTOM,			// マップを作成している状態
	END_CUSTOM,			// 作成終了後の保存時の状態
	MAX
};
class CustomMapScene :
	public BaseScene
{
public:
	CustomMapScene();
	~CustomMapScene();

	unique_Base Update(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::MAIN; }
private:
	void Draw()override;
	std::unique_ptr<Custom>map_;
	std::map<CustomState, std::function<void(void)>>updateFunc_;
	std::map<CustomState, std::function<void(void)>>drawFunc_;
	CustomState nowState_;
	int mapSizeX;
	int mapSizeY;
	TCHAR fileName[20];

	void SetStateUpdate();				// SET_STATEに対応するUpdate関数	
	void Map_CuntomUpdate();			// MAP_CUNSTOMに対応するUpdate関数
	void EndCustomUpdate();				// END_CUSTOMに対応するUpdate関数
	void SetStateDraw();				// SET_STATEに対応するDraw関数	
	void MapCuntomDraw();				// MAP_CUNSTOMに対応するDraw関数
	void EndCustomDraw();				// END_CUSTOMに対応するDraw関数

};

