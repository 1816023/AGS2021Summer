#pragma once
#include <memory>
#include "../KeyController.h"

enum class SCENE_ID
{
	TITLE,
	MAIN,
	CUSTOM,
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
	virtual unique_Base Update(unique_Base own) = 0;
	virtual void Draw();
	virtual void DrawUI();
	virtual SCENE_ID GetScnID(void) = 0;

protected:
	KEY_ARRAY now;
	KEY_ARRAY old;
};

