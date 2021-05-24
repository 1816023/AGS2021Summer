#pragma once
#include "../VECTOR2.h"
#include <vector>
#include <map>

#define CHIP_SIZE 32
#define MAP_SIZE 10
enum class NodeState
{
	None,		// �{�����Ă��Ȃ�
	Open,		// ���{����
	Closed,		// �{���I��
};

enum class MapState
{
	START,		// �X�^�[�g
	GOAL,		// �S�[��
	ROOT,		// �i�H
	ROAD,		// ��
	WALL,		// ��
};

struct Node
{
	Vec2Int pos;
	NodeState state;
	int cost;		// ���R�X�g
	int estCost;	// ����R�X�g
	Node* parent;	// �e�m�[�h
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
	// �m�[�h�����(�m�[�h�̃v�[������)
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

