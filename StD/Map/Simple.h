#pragma once
#include <map>
#include <list>
#include "Map.h"

class Simple :
	public Map
{
public:
	// 描画の中心座標
	Simple(VECTOR2 pos);
	~Simple();
	int Update();
	void Draw();
	bool SetUp(std::list<std::string> name);
	void SetSize(VECTOR2 size);
	bool SetMap(std::string path);
private:
	// 保存するマップ情報
	struct SimpleMapState {
		std::string path;
		VECTOR2 mapSize;
		VECTOR2 chip;
		dataVec mapData;
	};

	
	int screen_;
	VECTOR2 size_;
	VECTOR2 pos_;
	std::map<std::string, SimpleMapState>mapList_;
	std::string listKey_;
	bool CheckData(std::string path);

};

