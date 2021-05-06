#pragma once
#include <memory>
#include <array>
#include"VECTOR2.h"

#define lpMouseController MouseController::GetInstance()

class MouseController
{
public:
	static MouseController& GetInstance()
	{
		return (*s_Instans);
	}

	bool GetClickTrg(int mouseType);		// クリックした瞬間の場合、true
	bool GetClicking(int mouseType);		// クリック中の場合、true
	bool GetClickUp(int mouseType);			// クリックをやめた場合、true
	void Update(void);		// マウスの状態更新
	const VECTOR2& GetPos() { return pos; }	// マウスの位置の取得
	const int& GetWheel() { return wheel; }	// ホイールの取得
	const bool IsHitBoxToMouse(VECTOR2 lu, VECTOR2 rd);
private:
	struct MouseDelete
	{
		void operator()(MouseController* mouseController) const
		{
			delete mouseController;
		}
	};
	MouseController();
	~MouseController();

	VECTOR2 pos;	// マウスの座標
	char data;		// 現在のマウスのクリック状態
	char dataOld;	// 1フレーム前のマウスのクリック状態
	int wheel;		// ホイール増減値

	static std::unique_ptr<MouseController, MouseDelete> s_Instans;
};

