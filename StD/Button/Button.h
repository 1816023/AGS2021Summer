#pragma once
#include <functional>
#include <string>
#include "../VECTOR2.h"
enum class ButtonType
{
	Rect,
	Circle,
	RoundRect,
	BoxImage,
	CircleImage
};

class Button
{
public:
	Button(VECTOR2 offset);
	virtual ~Button();
	virtual void Update();
	// カーソルがある位置との当たり判定(マウスポジション指定)
	virtual bool IsHit(VECTOR2 mPos)=0;
	// カーソルがある位置との当たり判定(マウスポジション自動取得)
	virtual bool IsHit();
	// 押されたときに呼び出す
	virtual bool PushFunction() { return func_(); }
	// 押されてるかの取得
	virtual bool isPush() { return isPush_; }
	// ボタンの描画
	virtual void Draw()=0;
	// z軸の設定
	virtual void SetZbuff(int z);
	// z軸の取得デフォルトは0
	virtual int GetZBuff() { return zBuff_; }
	// ボタン上に描画する文字とその位置
	virtual void SetString(std::string str, VECTOR2 sPos);
protected:
	// 座標補正
	const VECTOR2 offset_;
	//現在押されているかのフラグ
	bool isPush_;
	// 当たり判定用の関数格納用
	std::function<bool(VECTOR2)>isHitFunc_;
	// 描画関数格納用
	std::function<void()>drawFunc_;
	// 
	bool isClick_;
	// Z軸
	int zBuff_;

	/*--引数を保管用--*/
	// 押されたときに呼び出される関数格納用
	std::function<bool()> func_;
	// 左上座標
	VECTOR2 lu_;
	// 右上座標
	VECTOR2 rd_;
	// 色
	int color_;
	// 座標
	VECTOR2 pos_;
	// 半径
	int radius_;
	// 角丸用の半径
	VECTOR2 radius2_;
	// 通常の画像パス
	std::wstring imagePath_;
	// 押下状態の時の画像パス
	std::wstring pushImagePath_;
	// 画像のサイズ
	VECTOR2 size_;
	// 描画文字
	std::string str_;
	// 文字描画位置
	VECTOR2 sPos_;
	/*------------------*/
	
	// どのタイプのボタンか
	ButtonType type_;
};

