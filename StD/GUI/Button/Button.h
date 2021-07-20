#pragma once
#include <functional>
#include <string>
#include "../../VECTOR2.h"
#include "../UI.h"
enum class ButtonType
{
	Rect,
	Circle,
	RoundRect,
	BoxImage,
	CircleImage
};

class Button : public UI
{
public:
	Button(VECTOR2 offset);
	virtual ~Button();
	virtual bool Update();
	// カーソルがある位置との当たり判定(マウスポジション指定)
	virtual bool IsHit(VECTOR2 mPos)=0;
	// カーソルがある位置との当たり判定(マウスポジション自動取得)
	const bool IsHit();
	// 押されたときに呼び出す
	const bool PushFunction() const { return func_(); }
	// 押されてるかの取得
	const bool IsPush() const { return isPush_; }
	// ボタンの描画
	virtual void Draw()=0;
	// z軸の設定
	void SetZbuff(int z);
	// z軸の取得デフォルトは0
	const int GetZBuff() const { return zBuff_; }
	// ボタン上に描画する文字とその位置
	void SetString(std::string str, VECTOR2 sPos, int fontHandle=-1);
	// アップデートで自動で当たり判定や判定処理を行うようになる
	void SetAuto();
	// クリックで押された時でなく離れたときに処理を行うようになる
	void SetReversePush();
	// DXLIBのMOUSE_INPUT_LEFT,MOUSE_INPUT_RIGHT,MOUSE_INPUT_WHEELのいずれかを指定する
	void SetClickType(int type);
	// 検索用のタグ設定
	void SetTag(int tag);
	// 検索用タグ取得
	const int GetTag() { return tag_; }
	// 押したときのサウンドハンドル設定
	// -2,指定なしでデフォルトのSEを設定
	void SetSound(int handle=-2);
	// strの取得
	const std::string GetStr()const { return str_; }
	// 拡大縮小スケールの設定
	void SetScale(float scale);
	// フォントを設定する
	void SetFont(int handle);
protected:
	// 座標補正
	const VECTOR2 offset_;
	//現在押されているかのフラグ
	bool isPush_;
	// 当たり判定用の関数格納用
	std::function<bool(VECTOR2)>isHitFunc_;
	// 描画関数格納用
	std::function<void()>drawFunc_;
	// Z軸
	int zBuff_;
	// 自動処理のフラグ
	bool autoFlag_;
	// 離れたときに処理をするかのフラグ
	bool reverseFlag_;
	// どのタイプのボタンか
	ButtonType type_;
	// DxLibのマウスクリックの判定でどの判定を使用するか
	// デフォルトはMOUSE_INPUT_LEFT
	int clickType_;
	// フォントハンドル
	int fontHandle_;
	// 検索用タグ
	int tag_;
	// ボタンを押したときのサウンドハンドル格納用
	int soundHandle_;
	// 拡大縮小スケール値
	float scale_;


	/*--引数を保管用--*/
	// 押されたときに呼び出される関数格納用
	std::function<bool()> func_;
	// 左上座標
	VECTOR2 lu_;
	// 右上座標
	VECTOR2 rd_;
	// 色
	int color_;
	//// 座標
	//VECTOR2 pos_;
	// 半径
	int radius_;
	// 角丸用の半径
	VECTOR2 radius2_;
	// 通常の画像パス
	std::wstring imagePath_;
	// 押下状態の時の画像パス
	std::wstring pushImagePath_;
	//// 画像のサイズ
	//VECTOR2 size_;
	// 描画文字
	std::string str_;
	// 文字描画位置
	VECTOR2 sPos_;
	/*------------------*/
	
};

