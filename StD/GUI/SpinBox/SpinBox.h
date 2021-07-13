#pragma once
#include "../../VECTOR2.h"
#include "../Button/ImageRectButton.h"
#include <vector>
#include<memory>
enum class BoxType
{
	INT,
	STRING,
	FLOAT,
	BOOL,
	IMAGE,
};
class SpinBox
{
public:
	// 
	SpinBox(VECTOR2 pos,int xSize,BoxType type, int fontHandle=-1);
	SpinBox(VECTOR2 pos,VECTOR2 size,BoxType type);
	virtual ~SpinBox();
	virtual bool Update();
	virtual void Draw()=0;
	const VECTOR2 GetPos()const { return pos_; }
	const int GetFontHandle()const { return fontHandle_; }
	const BoxType GetType()const { return type_; }
	const VECTOR2 GetSize()const { return size_; }

protected:
	VECTOR2 pos_;
	VECTOR2 size_;
	BoxType type_;
	int fontHandle_;
	std::pair<std::unique_ptr<ImageRectButton>, std::unique_ptr<ImageRectButton>>button_;
	int selKey_;
	int nowSize_;

};

