#pragma once
#include <DxLib.h>
#include <memory>
#include "Scene/BaseScene.h"


// �A�v���P�[�V�����܂Ƃ߃N���X
class Application
{
public:
	static Application& Instance()
	{
		static Application app;
		return app;
	}
	~Application()= default;
	bool Init();		// ������
	void Run();		// �X�V
	void Terminate();	// �㏈��

private:
	Application() = default;
	Application(const Application&) = delete;
	Application operator=(const Application&) = delete;

	void Draw();	// �`��

	std::unique_ptr<BaseScene>sceneController_;	// �V�[���R���g���[���[
};

