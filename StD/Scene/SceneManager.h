#pragma once
#include <memory>
#include "BaseScene.h"

#define lpSceneManager SceneManager::GetInstance()

class SceneManager
{
public:
	static SceneManager& GetInstance()
	{
		static SceneManager s_Instance;
		return s_Instance;
	}

	bool Run();

private:
	SceneManager();
	~SceneManager();
	bool SysInit(void);

	unique_Base sceneController;
};

