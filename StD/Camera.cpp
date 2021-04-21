#include "Camera.h"
#include <DxLib.h>

Camera::Camera()
{
	pos_ = Vec2Float(0.0f, 0.0f);
	scale_ = 1.0f;
}

Camera::~Camera()
{
}

void Camera::Control()
{
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		pos_.x++;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		pos_.x--;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		pos_.y++;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		pos_.y--;
	}
}

void Camera::SetScale(float scale)
{
	scale_ = scale;
}

const Vec2Float Camera::GetPos()
{
	return pos_;
}

const float Camera::GetScale()
{
	return scale_;
}
