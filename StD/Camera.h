#pragma once
#include "VECTOR2.h"

// �J�����N���X
class Camera
{
public:
	Camera();
	~Camera();

	void Control();				// �J�����ړ�
	void SetScale(float scale);	// �g�嗦�ύX
	const Vec2Float GetPos();	// ���W�擾
	const float GetScale();		// �g�嗦�擾
private:
	Vec2Float pos_;		// ���W
	float scale_;		// �g�嗦
};

