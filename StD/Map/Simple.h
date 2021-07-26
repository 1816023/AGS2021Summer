#pragma once
#include "Map.h"

struct SimpleMapState {
	std::string path;
	VECTOR2 size;
	std::vector<std::vector<int>>mapData;
};

class Simple :
	public Map
{
public:
	// •`‰æ‚Ì’†SÀ•W
	Simple(VECTOR2 pos);
	~Simple();
	int Update();
	void Draw();
	bool SetUp(std::string path)override;
	void SetSize(VECTOR2 size);
private:
	int screen_;
	VECTOR2 size_;
	VECTOR2 pos_;
};

