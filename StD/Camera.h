#pragma once
#include "VECTOR2.h"

#define DEF_SCALE 1.0f
#define CAMERA_MOVE 5

// カメラクラス
class MouseController;
class Camera
{
public:
	Camera();
	~Camera();

	// カメラ移動
	void Control();			
	// 拡大率変更
	void SetScale(float scale);
	// 座標取得
	const Vec2Float GetPos();
	// 拡大率取得
	const float GetScale();	
	void DebugDraw();
private:
	Vec2Float pos_;		// 座標
	float scale_;		// 拡大率
	Vec2Float beforePos_;		// 移動前座標
	VECTOR2 clickPos_;	// クリックした瞬間のマウスの座標
};

