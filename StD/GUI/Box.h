#pragma once
#include "UI.h"

class Box : public UI
{
public:
	// 箱(色と塗りつぶしをする)
	Box(VECTOR2 pos, VECTOR2 size, int color, bool fillF);
	// 箱(塗りつぶしの色を任意で設定する)
	Box(VECTOR2 pos, VECTOR2 size, int outColor,int inColor);

	// 更新
	bool Update();
	// 描画
	void Draw();
private:
	int outColor_;	// 外枠色(単色の場合この色が反映される)
	int inColor_;	// 内枠色
	bool fillF_;	// 内側を透過するかどうか
};

