#pragma once
#include <DxLib.h>
#include <memory>
#include "Scene/BaseScene.h"
#include "Camera.h"
#include <chrono>

#define DEF_SCREEN_SIZE_X 854
#define DEF_SCREEN_SIZE_Y 480

#define lpApplication Application::Instance()

class Camera;
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

	bool Init();			// ������
	void Run();				// �X�V
	void Terminate();		// �㏈��
	float GetDelta();		// �f���^�^�C��
	Camera& GetCamera();	// �J����

private:
	Application() = default;
	Application(const Application&) = delete;
	Application operator=(const Application&) = delete;

	void ExtendWindowInit();	// �E�C���h�E�T�C�Y�g�k������
	void Draw();	// �`��

	int gameScreen_;
	std::unique_ptr<BaseScene>sceneController_;	// �V�[���R���g���[���[
	std::unique_ptr<Camera>camera_;	// �J����

	std::chrono::system_clock::time_point old_;	// 1�t���[���O�̎���
	float delta_;
};

