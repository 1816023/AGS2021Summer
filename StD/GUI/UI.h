#pragma once
#include "../VECTOR2.h"
// UI���N���X
class UI
{
public:
	UI() = default;
	~UI() = default;
	virtual bool Update() = 0;
	// �{�^���̕`��
	virtual void Draw() = 0;
	VECTOR2 GetPos();
	void SetPos(const VECTOR2& pos);
	VECTOR2 GetSize();
protected:
	// ���W
	VECTOR2 pos_;
	// ���W
	VECTOR2 size_;
};

