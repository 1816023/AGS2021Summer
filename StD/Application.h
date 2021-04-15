#pragma once
#include <DxLib.h>
#include <memory>
#include "Scene/BaseScene.h"


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
	bool Init();		// 初期化
	void Run();		// 更新
	void Terminate();	// 後処理

private:
	Application() = default;
	Application(const Application&) = delete;
	Application operator=(const Application&) = delete;

	void Draw();	// 描画

	std::unique_ptr<BaseScene>sceneController_;	// シーンコントローラー
};

