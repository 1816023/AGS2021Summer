#pragma once
#include "VECTOR2.h"

#define DEF_SCALE 1.0f
#define CAMERA_MOVE 5

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
	void DebugDraw();
private:
	Vec2Float pos_;		// ���W
	float scale_;		// �g�嗦
	Vec2Float beforePos_;		// �ړ��O���W
	VECTOR2 clickPos_;	// �N���b�N�����u�Ԃ̃}�E�X�̍��W
};

