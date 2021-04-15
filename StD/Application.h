#pragma once
#include <DxLib.h>

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
	void Update();		// �X�V
	void Terminate();	// �㏈��

private:

	Application() = default;
	void Draw();		// �`��
};

