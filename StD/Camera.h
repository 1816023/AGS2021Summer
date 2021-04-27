#pragma once
#include "VECTOR2.h"

// カメラクラス
class Camera
{
public:
	Camera();
	~Camera();

	void Control();				// カメラ移動
	void SetScale(float scale);	// 拡大率変更
	const Vec2Float GetPos();	// 座標取得
	const float GetScale();		// 拡大率取得
private:
	Vec2Float pos_;		// 座標
	float scale_;		// 拡大率
};

