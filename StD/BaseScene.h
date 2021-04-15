#pragma once
#include <memory>

enum class SCENE_ID	// Scene管理用ID
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
	virtual unique_Base UpData(unique_Base own) = 0;	// アップデート関数
	virtual SCENE_ID GetScnID(void) = 0;				// ID管理関数
};

