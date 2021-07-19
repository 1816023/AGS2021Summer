#pragma once
#include "SpinBox.h"
class SpinBoxForFloat :
	public SpinBox
{
public:
	SpinBoxForFloat(VECTOR2 pos, int xSize,int NumOfDigits,int NumOfDigitsOfDecmal, int fontHandle = -1);
	~SpinBoxForFloat()override;
	void Draw()override;
	// 選択中のデータを取得する
	const float GetSelData()const;
	// データを挿入する
	void AddData(float data);
	void DeleteData();
	bool DeleteData(float data);
private:
	std::vector<float>vec_;
	// 表示桁数
	int NumOfDigits_;
	// 小数点以下の桁数
	int NumOfDigitsOfDecmal_;
};

