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

	bool Init();			// 初期化
	void Run();				// 更新
	void Terminate();		// 後処理
	float GetDelta();		// デルタタイム
	Camera& GetCamera();	// カメラ

private:
	Application() = default;
	Application(const Application&) = delete;
	Application operator=(const Application&) = delete;
	// ウインドウサイズ拡縮初期化
	void ExtendWindowInit();
	// 描画
	void Draw();	

	int gameScreen_;
	std::unique_ptr<BaseScene>sceneController_;	// シーンコントローラー
	std::unique_ptr<Camera>camera_;	// カメラ

	std::chrono::system_clock::time_point oldTime_;	// 1フレーム前の時間
	float delta_;
};

