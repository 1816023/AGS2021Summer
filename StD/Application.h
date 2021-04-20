#pragma once
#include <DxLib.h>
#include <memory>
#include "Scene/BaseScene.h"
#include <chrono>

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
	float getDelta();

private:
	Application() = default;
	Application(const Application&) = delete;
	Application operator=(const Application&) = delete;

	void ExtendWindowInit();	// �E�C���h�E�T�C�Y�g�k������
	void Draw();	// �`��


	int gameScreen_;
	int uiScreen_;
	std::unique_ptr<BaseScene>sceneController_;	// �V�[���R���g���[���[

	std::chrono::system_clock::time_point old;
	float delta;
};

