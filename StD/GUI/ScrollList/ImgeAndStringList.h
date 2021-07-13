#pragma once
#include "ScrollList.h"
struct IandSState
{
	int handle;
	VECTOR2 size;
	std::string str;
};
class ImgeAndStringList :
	public ScrollList
{
public:
	ImgeAndStringList(VECTOR2 pos, VECTOR2 size);
	~ImgeAndStringList()override;
	// リストの最後に要素を追加する
	bool Add(int handle,std::string str);
	// リストの最後の要素を削除する
	bool Del();

	void Update()override;
	void Draw()override;

private:
	std::list<IandSState>list_;

};

