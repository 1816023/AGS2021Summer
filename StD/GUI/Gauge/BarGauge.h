#pragma once
#include "../UI.h"
class BarGauge :
	public UI
{
public:
	BarGauge(VECTOR2 pos,VECTOR2 size,int maxGauge );
	~BarGauge()override;
	bool Update()override;
	void Draw()override;

	// 値の増加
	int Add(int num);
	// 値の減少
	int Sub(int num);
	// 値を文字として表示
	void SetViewNumber(VECTOR2 pos);
	// 色の設定
	// 初期色はゲージが黒で縁が白
	void SetColor(int gaugeColor = 0, int frameColor = 0xffffff);
	// 背景を埋める
	void SetBackColor(bool isView, int color);
	// ゲージの最大値を変更する
	void ChangeMaxGauge(int num);
private:
	int gauge_;
	bool isView_;
	bool isBackColor;
	int gaugeColor_;
	int frameColor_;
	int backColor_;
	int maxGauge_;
	VECTOR2 strPos_;
};

