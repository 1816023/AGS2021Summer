#pragma once
#include "ScrollList.h"
struct BoxState
{
	VECTOR2 size;
	int color;
};

class BoxList : public ScrollList
{
public:
	BoxList(VECTOR2 pos, VECTOR2 size);
	~BoxList()override;
	// リストの最後に要素を追加する
	bool Add(BoxState state);
	// リストの最後の要素を削除する
	bool Del();

	void Update()override;
	void Draw()override;

private:
	std::list<BoxState>list_;
	int color_;
};

