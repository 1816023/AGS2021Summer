#pragma once
#include "BaseScene.h"
#include "../Map/Custom.h"
#include <functional>
#include <memory>
#include <map>
#include <list>
#include "../GUI/Button/RoundRectButton.h"
#include "../CustomState/CustomState.h"
#define MAX_NAME_SIZE 20	// ファイル名の最大文字数
#define STRING_HIGHT 20		// 文字の高さ
#define LINE_SPACING 30		// 行間
#define SELECT_UI_POS std::pair<VECTOR2,VECTOR2>(VECTOR2(static_cast<int>(DEF_SCREEN_SIZE_X/1.5f),0),VECTOR2(DEF_SCREEN_SIZE_X,DEF_SCREEN_SIZE_Y))
#define TEXT_UI_POS std::pair<VECTOR2,VECTOR2>(VECTOR2(0,static_cast<int>(DEF_SCREEN_SIZE_Y/1.25f)),VECTOR2(SELECT_UI_POS.first.x-10,DEF_SCREEN_SIZE_Y))

enum class CustomState {
	SELECT_FILE,		// 既存のファイルから選択する
	SET_STATE,			// マップの幅や高さを設定する状態
	MAP_CUSTOM,			// マップを作成している状態
	ROOT_CUSTOM,		// ルートを作成する状態
	ENEMY_CUSTOM,		// 敵の配置と敵の侵攻ルート設定
	END_CUSTOM,			// 作成終了後の保存時の状態
	MAX
};
struct ButtonText
{
	std::string str_;		// 文章
	unsigned int color_;	// 文字色
	VECTOR2 pos_;			// 描画位置
};


class Astar;
class SelectFile;
class SetState;
class MapCustom;
class EnemyCustom;
class EndCustom;
class RootCustom;
class Canvas;
enum class ErrorCode : int;
class CustomMapScene :
	public BaseScene
{
public:
	CustomMapScene();
	~CustomMapScene();

	unique_Base Update(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::CUSTOM; }
private:
	// 初期化用
	bool Init();
	// 基本的なメイン物の描画
	void Draw()override;
	// UI系の描画
	void DrawUI()override;
	// customクラスのポインター
	std::unique_ptr<Custom>cusMap_;
	// --- キャンバス
	// メインのUIキャンバス
	std::unique_ptr<Canvas>canvas_;
	// テキスト表示用キャンバス
	std::unique_ptr<Canvas>textCanvas_;
	// 常時表示用のキャンバス
	std::unique_ptr<Canvas>alwaysCanvas_;
	// マップ
	std::map<CustomState, std::unique_ptr<CustomStateBase>>custom_;
	// 現在のステータス
	CustomState nowState_;
	// マップファイル名の保存用
	TCHAR fileName_[20];
	// 変動するアルファ値
	int blendAlpha_;
	// ファイルからロードした説明文
	std::map<MapChipName,std::string> textData_;
	// タイトル遷移する用のフラグ
	bool isTitleTransition_;
	// 保存するときに最低限の状態になっているかの
	// return 0 エラーなし
	// return 1 自拠点敵拠点の数異常
	// return 2 自拠点の数異常
	// return 3 敵拠点の数異常
	ErrorCode SaveCheck();
	// 入力されたファイル名にエラーがないかチェックする,trueならエラー
	bool FileNameErrorCheck(std::wstring fileName);
	// 説明文をファイルからロードする
	bool LoadText(std::string type);

	friend SelectFile;
	friend SetState;
	friend MapCustom;
	friend EnemyCustom;
	friend EndCustom;
	friend RootCustom;
};

