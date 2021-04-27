#pragma once
#include "BaseScene.h"
#include "../Map/Custom.h"
#include <functional>
#include <memory>
#include <map>

#define MAX_NAME_SIZE 20	// ファイル名の最大文字数
#define STRING_HIGHT 20		// 文字の高さ
#define LINE_SPACING 30		// 行間
#define SELECT_UI_DRAW std::pair<VECTOR2,VECTOR2>(VECTOR2(DEF_SCREEN_SIZE_X/1.5,0),VECTOR2(DEF_SCREEN_SIZE_X,DEF_SCREEN_SIZE_Y))
#define TEXT_UI_DRAW std::pair<VECTOR2,VECTOR2>(VECTOR2(0,DEF_SCREEN_SIZE_Y/1.5),VECTOR2(SELECT_UI_DRAW.first.x-10,DEF_SCREEN_SIZE_Y))

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
	// 基本的なメイン物の描画
	void Draw()override;
	// UI系の描画
	void DrawUI()override;
	// customクラスのポインター
	std::unique_ptr<Custom>map_;
	// 各ステータスごとのアップデート関数格納用function
	std::map<CustomState, std::function<void(void)>>updateFunc_;
	// 各ステータスごとの描画用関数格納用function,基本的にはUI系
	std::map<CustomState, std::function<void(void)>>drawFunc_;
	// 現在のステータス
	CustomState nowState_;
	// マップサイズ入力の保存用
	int mapSizeX;
	int mapSizeY;
	// マップファイル名の保存用
	TCHAR fileName[20];
	// 変動するアルファ値
	int blendAlpha;

	// SET_STATEに対応するUpdate関数
	void SetStateUpdate();					
	// MAP_CUNSTOMに対応するUpdate関数
	void Map_CuntomUpdate();			
	// END_CUSTOMに対応するUpdate関数
	void EndCustomUpdate();				
	// SET_STATEに対応するDraw関数
	void SetStateDraw();				
	// MAP_CUNSTOMに対応するDraw関数
	void MapCustomDraw();				
	// END_CUSTOMに対応するDraw関数
	void EndCustomDraw();				
	// 入力されたファイル名にエラーがないかチェックする,trueならエラー
	bool FileNameErrorCheck(std::wstring fileName);
};

