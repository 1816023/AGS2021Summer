#pragma once
#include "Map.h"
class Simple :
	public Map
{
public:
	Simple();
	~Simple();
	int Update();
	void Draw();
	void SetMap(std::string path);
	void SetSize(VECTOR2 size);
private:
	int screen_;
	VECTOR2 size_;
	VECTOR2 pos_;
};

