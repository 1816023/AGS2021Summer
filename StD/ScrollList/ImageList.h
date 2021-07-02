#pragma once
#include "ScrollList.h"
class ImageList :
	public ScrollList
{
public:
	ImageList(VECTOR2 pos, VECTOR2 size, ListType type);
	~ImageList()override;
	// リストの最後に要素を追加する
	bool Add(int handle);
	// リストの最後の要素を削除する
	bool Del();

	void Update()override;
	void Draw()override;

private:
	std::list<int>list_;

};

