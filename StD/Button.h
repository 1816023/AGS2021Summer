#pragma once
#include <functional>
#include <string>
#include "VECTOR2.h"
enum class ButtonType
{
	Box,
	Circle,
	RoundRect,
	BoxImage,
	CircleImage
};
class Button
{
public:
	// 単色の四角いボタン
	Button(VECTOR2 lu,VECTOR2 rd,int color,std::function<bool()> func,VECTOR2 offset);
	// 単色の丸いボタン
	Button(VECTOR2 pos, int radius, int color, std::function<bool()>func, VECTOR2 offset);
	// 単色の角丸のボタン
	Button(VECTOR2 lu, VECTOR2 rd, VECTOR2 radius, int color, std::function<bool()>func, VECTOR2 offset);
	// 画像を用いた四角いボタン
	Button(VECTOR2 pos, VECTOR2 size, std::wstring imagePath, std::wstring pushImagePath,std::function<bool()>func , VECTOR2 offset);
	// 画像を用いた丸いボタン	
	Button(VECTOR2 pos, int radius, std::wstring imagePath, std::wstring pushImagePath, std::function<bool()>func, VECTOR2 offset);
	~Button();
	// カーソルがある位置との当たり判定(マウスポジション指定)
	bool IsHit(VECTOR2 mPos);
	// カーソルがある位置との当たり判定(マウスポジション自動取得)
	bool IsHit();
	// 押されたときに呼び出す
	bool PushFunction() { return func_(); };
	// 押されてるかの取得
	bool isPush() { return isPush_; }
	// ボタンの描画
	void Draw();
private:
	// 各ボタンごとの当たり判定
	bool BoxHit(VECTOR2 mPos);
	bool CircleHit(VECTOR2 mPos);
	bool RoundRectHit(VECTOR2 mPos);
	bool BoxImageHit(VECTOR2 mPos);
	bool CircleImageHit(VECTOR2 mPos);
	// 各ボタンごとの描画
	void BoxDraw();
	void CircleDraw();
	void RoundRect();
	void BoximageDraw();
	void CircleImageDraw();
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
	/*引数を保管用*/
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
	// どのタイプのボタンか
	ButtonType type_;
};

