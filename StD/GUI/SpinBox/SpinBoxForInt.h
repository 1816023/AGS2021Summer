#pragma once
#include "SpinBox.h"
class SpinBoxForInt :
	public SpinBox
{
public:
	SpinBoxForInt(VECTOR2 pos, int xSize, int fontHandle = -1);
	~SpinBoxForInt()override;
	bool Update()override;
	void Draw()override;
	// 選択中のデータを取得する
	const int GetSelData()const;
	// データを挿入する
	void AddData(int data);
	bool DeleteData();
	bool DeleteData(int data);
private:
	std::vector<int>vec_;
};

