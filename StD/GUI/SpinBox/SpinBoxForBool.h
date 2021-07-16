#pragma once
#include "SpinBox.h"
#include <array>
class SpinBoxForBool :
	public SpinBox
{
public:
	SpinBoxForBool(VECTOR2 pos, int xSize, int fontHandle = -1);
	~SpinBoxForBool ()override;
	void Draw()override;
	// 選択中のデータを取得する
	const int GetSelData()const;
private:
	std::array<bool,2>array_;

};

