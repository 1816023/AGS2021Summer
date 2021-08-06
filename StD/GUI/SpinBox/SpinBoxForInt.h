#pragma once
#include "SpinBox.h"
class SpinBoxForInt :
	public SpinBox
{
public:
	SpinBoxForInt(VECTOR2 pos, int xSize,  VECTOR2 cOffset, int fontHandle = -1);
	~SpinBoxForInt()override;
	void Draw()override;
	// 選択中のデータを取得する
	const int GetSelData()const;
	// データを挿入する
	void AddData(int data);
	void DeleteData();
	bool DeleteData(int data);
	void StartEnd(bool key)override;
private:
	std::vector<int>vec_;
};

