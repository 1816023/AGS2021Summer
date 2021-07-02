#pragma once
#include <list>
#include <array>
#include <string>
#include <memory>
#include "../VECTOR2.h"
enum class ListType
{
	STRING,
	IMAGE,
	COLOR_BOX,
	Max
};

class ScrollList
{
public:
	
	ScrollList(VECTOR2 pos,VECTOR2 size,ListType type);
	virtual ~ScrollList();
	virtual bool Del()=0;
	virtual void Update()=0;
	virtual void Draw()=0;
private:
protected:
	// スクロール量
	float scrollPos_;
	// 描画位置（左上）
	VECTOR2 pos_;
	// 描画サイズ
	VECTOR2 size_;
	// リストタイプ
	ListType type_;
	// 描画スクリーン
	int screen_;

};

