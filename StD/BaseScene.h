#pragma once
#include <memory>

enum class SCENE_ID	// Scene�Ǘ��pID
{
	TITLE,
	MAIN,
	GAME,
	RESULT,
	MAX
};

class BaseScene;
using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene() {}
	virtual ~BaseScene() {}
	virtual unique_Base UpData(unique_Base own) = 0;	// �A�b�v�f�[�g�֐�
	virtual SCENE_ID GetScnID(void) = 0;				// ID�Ǘ��֐�
};

