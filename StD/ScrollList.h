#pragma once
#include <list>
#include <array>
#include <string>
#include <memory>
#include "./VECTOR2.h"
enum class ListType
{
	STRING,
	IMAGE,
	COLOR_BOX,
	Max
};

struct BoxState
{
	VECTOR2 size;
	int color;
};
struct StringState 
{
	std::string str;
	int color;
};
class ScrollList
{
public:
	
	ScrollList(VECTOR2 pos,VECTOR2 size,ListType type,int fonthande=-1);
	~ScrollList();
	// string型の要素追加
	// 自身と同じタイプじゃない場合falseを返す
	bool Add(StringState state);
	// 画像型の要素追加
	// 自身と同じタイプじゃない場合falseを返す
	bool Add(int handle);
	// 色箱ごとの要素追加
	// 自身と同じタイプじゃない場合falseを返す
	bool Add(BoxState state);
	
	void Update();
	void Draw();
private:
	// スクロール量
	int scrollPos_;
	// 描画位置（左上）
	VECTOR2 pos_;
	// 描画サイズ
	VECTOR2 size_;
	// リストタイプ
	ListType type_;
	// string型用のリスト
	std::list<StringState>slist_;
	// 画像型用のリスト
	std::list<int>ilist_;
	// 色箱型のリスト
	std::list<BoxState>blist_;
	// 描画スクリーン
	int screen_;
	// string型仕様用のフォントハンドル
	int fontH_;

	void sDraw();
	void iDraw();
	void bDraw();
};

