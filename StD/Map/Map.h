#pragma once
#include "../VECTOR2.h"
#include <string>
#include <vector>
#include "../tinyxml2/tinyxml2.h"

// チップ情報の名前
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
// マップ情報の表示取得用クラス
class Map
{
public:
	Map();
	virtual ~Map();
	virtual int Update();
	virtual void Draw();
	// マップ情報の初期化、マップデータの名前(拡張子なし)を指定
	virtual bool SetUp(std::string mapName);		
	// チップ情報の取得、ほしい場所のポジションを指定(float)	
	MapChipName GetMapChip(Vec2Float pos);			
	// チップ情報の取得、ほしい場所のポジションを指定(int)
	MapChipName GetMapChip(VECTOR2 pos);			
	// マップサイズ取得
	VECTOR2 GetMapSize();							
	// チップサイズ取得	
	VECTOR2 GetChipSize();							
protected:
	// マップをロードする、マップデータの名前(拡張子なし)を指定
	bool LoadMap(std::string mapName);				
	// マップのchip数
	VECTOR2 mapSize_;								
	// 1chipのサイズ
	VECTOR2 chipSize_;								
	// マップデータの格納2次元配列
	dataVec mapData_;								
	// マップデータのXMLファイルをロードしたデータ
	tinyxml2::XMLDocument document;					
};


