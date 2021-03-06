#pragma once
#include "SpinBox.h"
class SpinBoxForString :
	public SpinBox
{
public:
	SpinBoxForString(VECTOR2 pos, int xSize, VECTOR2 cOffset, int fontHandle = -1);
	~SpinBoxForString()override;
	bool Update()override;
	void Draw()override;
	// 選択中のデータを取得する
	const std::string GetSelData()const;
	// データを挿入する
	void AddData(std::string data);
	// データを削除する
	void DeleteData();
	// 指定したデータを削除する
	bool DeleteData(std::string data);
	void StartEnd(bool key)override;
private:
	std::vector<std::string>vec_;

};

