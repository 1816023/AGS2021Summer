#pragma once
#include "VECTOR2.h"

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
private:
	Vec2Float pos_;		// 座標
	float scale_;		// 拡大率
	VECTOR2 clickPos_;	// クリックした瞬間のマウスの座標
};

