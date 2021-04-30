#include "Camera.h"
#include <DxLib.h>
#include "MouseController.h"

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
	auto wheel = static_cast<float>(lpMouseController.GetWheel());
	if (wheel != 0)
	{
		scale_ = 1 + wheel * 0.01f;
	}
	if (lpMouseController.GetClickTrg(MOUSE_INPUT_RIGHT))
	{
		clickPos_ = lpMouseController.GetPos();
	}
	if (lpMouseController.GetClickUp(MOUSE_INPUT_RIGHT))
	{
		clickPos_ = VECTOR2(0, 0);
	}

	if (lpMouseController.GetClicking(MOUSE_INPUT_RIGHT))
	{
		auto dist = lpMouseController.GetPos() - clickPos_;
		if (dist != VECTOR2(0.0f, 0.0f))
		{
			auto nVec = dist.Normarize();
			pos_ -= nVec * 3.0f;
		}
	
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
