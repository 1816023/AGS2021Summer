#pragma once
#include <list>
#include <memory>
#include "../../VECTOR2.h"
#include "../Button/RectButton.h"
class PullDown
{
public:
	PullDown(VECTOR2 pos,int xSize);
	~PullDown();
	bool Add(std::string str);
	void Update();
	void Draw();
private:
	int screen_;
	VECTOR2 size_;
	VECTOR2 pos_;
	int selKey_;
	std::list<std::unique_ptr<RectButton>>list_;
	bool openFlag_;

};

