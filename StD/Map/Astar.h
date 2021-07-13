#pragma once
#include "../VECTOR2.h"
#include <vector>
#include <map>
#include "../Unit/Enemy/EnemyType.h"
enum class NodeState
{
	None,		// 捜索していない
	Open,		// 今捜索中
	Closed,		// 捜索終了
};


class Custom;
class Astar
{
public:
	Astar(Custom& map);
	// A*でルート作成
	std::vector<RootDir> AstarStart(VECTOR2 start, VECTOR2 goal);
	void Draw();
private:
	struct Node
	{
		Vec2Int pos;		// 座標
		NodeState state;	// 捜索状態
		int cost;		// 実コスト
		int estCost;	// 推定コスト
		Node* parent;	// 親ノード
		Node()
		{
			pos = { 0,0 };
			state = NodeState::None;
			cost = 0;
			estCost = 0;
			parent = nullptr;
		}
		Node(VECTOR2 p)
		{
			pos = p;
			state = NodeState::None;
			cost = 0;
			estCost = 0;
			parent = nullptr;
		}
	};
	// 周りのノードをオープンする
	void OpenAround(const Node& node);
	// ノードをオープンする
	void OpenNode(VECTOR2 pos, const Node& node);
	// 範囲外チェック
	bool IsOutOfRange(const VECTOR2& pos);
	// プールからノードを取得(ない場合は新規作成)
	Node& GetNode(VECTOR2 pos);
	// ノードを閉じる(ノードのプールから)
	void CloseNode(VECTOR2 pos);
	// 再帰的にルートを作成する
	void RecursiveCreateRoot(Node& node);
	// 座標からインデックスを取得
	int GetIdx(const VECTOR2 pos);

	VECTOR2 start_;	// スタートのード
	VECTOR2 goal_;	// ゴールノード
	std::map<int,Node> nodePool_;	// ノードを一時保存しているもの
	std::vector<Node> openList_;	// オープンしているノードのリスト
	std::vector<RootDir> root_;		// ルート
	Custom& cusMap_;
};

