#pragma once
#include "ScrollList.h"
struct ImageState {
	int handle;
	VECTOR2 size;
};
class ImageList :
	public ScrollList
{
public:
	ImageList(VECTOR2 pos, VECTOR2 size);
	~ImageList()override;
	// リストの最後に要素を追加する
	bool Add(int handle);
	// リストの最後の要素を削除する
	bool Del();

	void Update()override;
	void Draw()override;

private:
	std::list<ImageState>list_;

};

