#pragma once
#include "ScrollList.h"
struct StringState
{
	std::string str;
	int color;
};

class StringList :
	public ScrollList
{
public:
	StringList(VECTOR2 pos, VECTOR2 size, int fonthande = -1);
	~StringList()override;
	// リストの最後に要素を追加する
	bool Add(StringState state);
	// リストの最後の要素を削除する
	bool Del();

	void Update()override;
	void Draw()override;
private:
	// string型仕様用のフォントハンドル
	int fontH_;

	std::list<StringState>list_;
};

