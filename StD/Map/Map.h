#pragma once
#include "../VECTOR2.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "../tinyxml2/tinyxml2.h"
#include "../Unit/Enemy/EnemyType.h"


// チップ情報の名前
enum class MapChipName:unsigned int
{

	MAINSTAY=1,		// 防衛拠点				青
	SPAWNER,		// 敵出現位置			黄
	ROOT,			// 敵侵攻ルート			赤
	FIELD,			// 自機配置可能箇所		灰/白
	WALL,			// 自機配置不可能箇所	黒（背景色）
	MAX

};
using mapChipVec = std::vector<MapChipName>;

// 
struct MapState
{
	VECTOR2 mapSize;
	VECTOR2 chipSize;
	std::wstring name_;

};
using dataVec = std::vector<std::vector<MapChipName>> ;
using rootVec = std::vector<RootDir> ;
using enemyList = std::vector<EnemyData>;	// 敵リスト
using spawnEList = std::vector<enemyList>;	// スポナーごとの敵リスト
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
	// チップ情報の取得、ほしい場所のインデックスを指定(int)
	MapChipName GetMapChipByIndex(VECTOR2 idx);
	// マップサイズ取得
	VECTOR2 GetMapSize();							
	// チップサイズ取得	
	VECTOR2 GetChipSize();		
	void FindMapObj(mapChipVec& map, const int& y, mapChipVec::iterator fStart);
	// 自拠点の位置を取得する
	const std::vector<int>& GetMainStay();
	// スポナーの位置を取得する
	const std::vector<int>& GetSpawner();
	// ルートを取得する
	const std::vector<rootVec>& GetRoot();
	// ルートをセットする
	void SetRoot(const std::vector<rootVec>& root);
	// ドキュメントの取得
	const tinyxml2::XMLDocument GetDoc(tinyxml2::XMLDocument& doc);
	// ドキュメントの保存
	tinyxml2::XMLError SaveXMLFile(tinyxml2::XMLDocument& doc);
	// インデックスを座標に
	VECTOR2 PosFromIndex(int index);
	// ウェーブごとのスポナー別敵リスト取得
	std::unordered_map<int, spawnEList>& GetEnemyDatas();
	// ルートがいくつあるのかを取得
	int GetRootNum();
protected:
	// マップをロードする、マップデータの名前(拡張子なし)を指定
	bool LoadMap(std::string mapName);	
	// ルートをロードする
	void LoadRoot();
	// マップのステータス
	MapState state_;						
	// マップデータの格納2次元配列
	dataVec mapData_;								
	// マップデータのXMLファイルをロードしたデータ
	tinyxml2::XMLDocument document_;
	// インデックスを格納
	// ※インデックスはx+y*xの最大
	// 拠点座標
	std::vector<int> mainStay_;
	// 敵出現位置の座標
	std::vector<int>spawners_;
	// ウェーブごとのスポナー別敵リスト
	std::unordered_map<int, spawnEList> enemyDatas_;
	// ルート
	std::vector<rootVec>root_;
	// 開いてるファイルのパス
	std::string filePath;

};


