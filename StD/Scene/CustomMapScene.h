#pragma once
#include "BaseScene.h"
#include "../Map/Custom.h"
#include <functional>
#include <memory>
#include <map>
#include <list>
#include "../Button/RoundRectButton.h"
#include "../CustomState/CustomState.h"
#define MAX_NAME_SIZE 20	// ファイル名の最大文字数
#define STRING_HIGHT 20		// 文字の高さ
#define LINE_SPACING 30		// 行間
#define SELECT_UI_POS std::pair<VECTOR2,VECTOR2>(VECTOR2(DEF_SCREEN_SIZE_X/1.5,0),VECTOR2(DEF_SCREEN_SIZE_X,DEF_SCREEN_SIZE_Y))
#define TEXT_UI_POS std::pair<VECTOR2,VECTOR2>(VECTOR2(0,DEF_SCREEN_SIZE_Y/1.25),VECTOR2(SELECT_UI_POS.first.x-10,DEF_SCREEN_SIZE_Y))
struct ButtomState {
	VECTOR2 luPos;		// 左上座標
	VECTOR2 rdPos;		// 右上座標
	bool pushFlag;		// 押下フラグ
	std::wstring name;	// ボタンの名前
	int CorH;			// ボタンの色または画像ハンドル
	std::function<void(ButtomState&)> func;	// ボタンが押されたときに呼ばれる関数
};

enum class CustomState {
	SELECT_FILE,		// 既存のファイルから選択する
	SET_STATE,			// マップの幅や高さを設定する状態
	MAP_CUSTOM,			// マップを作成している状態
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
class CustomMapScene :
	public BaseScene
{
public:
	CustomMapScene();
	~CustomMapScene();

	unique_Base Update(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::MAIN; }
private:
	// 初期化用
	bool Init();
	// 基本的なメイン物の描画
	void Draw()override;
	// UI系の描画
	void DrawUI()override;
	// customクラスのポインター
	std::unique_ptr<Custom>cusMap_;
	
	//
	std::map<CustomState, std::unique_ptr<CustomStateBase>>custom_;
	// 現在のステータス
	CustomState nowState_;
	// マップファイル名の保存用
	TCHAR fileName_[20];
	// 変動するアルファ値
	int blendAlpha_;
	// ファイルからロードした説明文
	std::map<MapChipName,std::string> textData_;
	// 保存するときに最低限の状態になっているかの
	// return 0 エラーなし
	// return 1 自拠点敵拠点の数異常
	// return 2 自拠点の数異常
	// return 3 敵拠点の数異常
	int SaveCheck();
	// 入力されたファイル名にエラーがないかチェックする,trueならエラー
	bool FileNameErrorCheck(std::wstring fileName);
	// 説明文をファイルからロードする
	bool LoadText(std::string type);

	friend SelectFile;
	friend SetState;
	friend MapCustom;
	friend EnemyCustom;
	friend EndCustom;
};

