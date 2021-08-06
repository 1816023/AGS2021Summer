#pragma once
#include "SpinBox.h"
class SpinBoxForImage :
	public SpinBox
{
public:
	SpinBoxForImage(VECTOR2 pos, VECTOR2 size, VECTOR2 cOffset);
	~SpinBoxForImage()override;
	void Draw()override;
	// 選択中のデータを取得する
	// 画像ハンドルを返す
	const int GetSelData()const;
	// データを挿入する
	// 画像パスを指定する
	void AddData(std::string path);
	// データを挿入する
	// 画像ハンドルを指定する
	void AddData(int handle);
	// データを削除する
	void DeleteData();
	// 指定したデータを削除する
	// 画像パスを指定する
	bool DeleteData(std::string data);
	// 指定したデータを削除する
	// 画像ハンドルを指定する
	bool DeleteData(int data);
	void StartEnd(bool key)override;
private:
	std::vector<int>vec_;

};

