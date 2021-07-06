#include "Camera.h"
#include <DxLib.h>
#include "MouseController.h"

Camera::Camera()
{
	pos_ = Vec2Float(0.0f, 0.0f);
	scale_ = 1.0f;
	beforePos_ = Vec2Float(0.0f, 0.0f);
	clickPos_ = VECTOR2(0, 0);
	scaleLock_ = false;
}

Camera::~Camera()
{
}

void Camera::Control()
{
	/*if (CheckHitKey(KEY_INPUT_LEFT))
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
	}*/
	if (CheckHitKey(KEY_INPUT_ADD))
	{
		pos_.x += 32;
	}
	if (CheckHitKey(KEY_INPUT_SUBTRACT))
	{
		pos_.x += 64;
	}
	if (CheckHitKey(KEY_INPUT_MULTIPLY))
	{
		pos_.x += 128;
	}
	if (!scaleLock_)
	{
		auto wheel = static_cast<float>(lpMouseController.GetWheel());
		scale_ += roundf(wheel * 0.01f);
	}
	
	if (lpMouseController.GetClickTrg(MOUSE_INPUT_RIGHT))
	{
		clickPos_ = lpMouseController.GetPos();
		beforePos_ = pos_;
	}
	if (lpMouseController.GetClickUp(MOUSE_INPUT_RIGHT))
	{
		clickPos_ = VECTOR2(0, 0);
		beforePos_ = Vec2Float(0.0f,0.0f);
	}

	if (lpMouseController.GetClicking(MOUSE_INPUT_RIGHT))
	{
		auto dist = lpMouseController.GetPos() - clickPos_;
		if (dist != VECTOR2(0, 0))
		{
			auto distF = VecFCast(dist);
			// 1.0fÇÕíËêî
			// scale_Ç™1ÇÃéû2Ç…Ç»ÇÈ
			pos_ = beforePos_ - distF * scale_;
		}
	}
	if (CheckHitKey(KEY_INPUT_R))
	{
		pos_ = Vec2Float(0.0f, 0.0f);
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

void Camera::ScaleLock(bool lock)
{
	scaleLock_ = lock;
}

void Camera::DebugDraw()
{
	auto dist = lpMouseController.GetPos() - clickPos_;
	DrawFormatString(0, 0, 0xffffff, L"dist %d, %d", dist.x, dist.y);
}
