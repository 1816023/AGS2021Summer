#pragma once
#include "../VECTOR2.h"
#include <vector>
#include <map>

#define CHIP_SIZE 32
#define MAP_SIZE 10
enum class NodeState
{
	None,		// 捜索していない
	Open,		// 今捜索中
	Closed,		// 捜索終了
};

enum class MapState
{
	START,		// スタート
	GOAL,		// ゴール
	ROOT,		// 進路
	ROAD,		// 道
	WALL,		// 壁
};

struct Node
{
	Vec2Int pos;
	NodeState state;
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
class Astar
{
public:
	Astar();
	void Draw();
private:
	void OpenAround(Node& node);
	Node* OpenNode(VECTOR2 pos, Node& node);
	bool IsOutOfRange(const VECTOR2& pos);
	Node& GetNode(VECTOR2 pos);
	// ノードを閉じる(ノードのプールから)
	void CloseNode(VECTOR2 pos);
	void RecursiveCreateRoot(Node& node);
	int GetIdx(const VECTOR2 pos);

	VECTOR2 start_;
	VECTOR2 goal_;
	std::map<int,Node> nodePool_;
	std::vector<Node> openList_;
	std::vector<Node> root;
	std::vector<std::vector<MapState>> mapData_;
};

