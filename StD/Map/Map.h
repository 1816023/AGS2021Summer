#pragma once
#include "../VECTOR2.h"
#include <string>
#include <vector>
#include "../tinyxml2/tinyxml2.h"

enum class MapChipName:char
{

	MAINSTAY=1,		// 防衛拠点
	SPAWNER,		// 敵出現位置
	ROOT,			// 敵侵攻ルート
	FIELD,			// 自機配置可能箇所
	WALL,			// 自機配置不可能箇所
	MAX

};
using dataVec = std::vector<std::vector<MapChipName>> ;
class Map
{
public:
	Map();
	virtual ~Map();
	virtual int Update();
	virtual void Draw();
	virtual bool SetUp(std::string mapName);		// マップ情報の初期化、マップデータの名前(拡張子なし)を指定
	MapChipName GetMapChip(Vec2Float pos);			// チップ情報の取得、ほしい場所のポジションを指定(float)	
	MapChipName GetMapChip(VECTOR2 pos);			// チップ情報の取得、ほしい場所のポジションを指定(int)
	VECTOR2 GetMapSize();							// マップサイズ取得
	VECTOR2 GetChipSize();							// チップサイズ取得	
protected:
	bool LoadMap(std::string mapName);				// マップをロードする、マップデータの名前(拡張子なし)を指定
	VECTOR2 mapSize_;								// マップのchip数
	VECTOR2 chipSize_;								// 1chipのサイズ
	dataVec mapData_;								// マップデータの格納2次元配列
	tinyxml2::XMLDocument document;					// マップデータのXMLファイルをロードしたデータ
};


