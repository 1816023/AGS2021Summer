#pragma once
#include <DxLib.h>

// アプリケーションまとめクラス
class Application
{
public:
	static Application& Instance()
	{
		static Application app;
		return app;
	}
	~Application()= default;
	void Init();	// 初期化
	void Update();	// 更新
	void Draw();	// 描画

private:
	Application() = default;
};

