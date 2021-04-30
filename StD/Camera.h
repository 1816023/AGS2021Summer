#pragma once
#include "VECTOR2.h"

// �J�����N���X
class MouseController;
class Camera
{
public:
	Camera();
	~Camera();

	// �J�����ړ�
	void Control();			
	// �g�嗦�ύX
	void SetScale(float scale);
	// ���W�擾
	const Vec2Float GetPos();
	// �g�嗦�擾
	const float GetScale();	
private:
	Vec2Float pos_;		// ���W
	float scale_;		// �g�嗦
	VECTOR2 clickPos_;	// �N���b�N�����u�Ԃ̃}�E�X�̍��W
};

