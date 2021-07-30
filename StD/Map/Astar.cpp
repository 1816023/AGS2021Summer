#include "Astar.h"
#include <DxLib.h>
#include <array>
#include <algorithm>
#include "Custom.h"

Astar::Astar(Custom& map): cusMap_(map)
{
}

std::vector<RootDir> Astar::AstarStart(VECTOR2 start, VECTOR2 goal)
{
	if (!openList_.empty())
	{
		openList_.clear();
	}
	if (!root_.empty())
	{
		root_.clear();
	}
	if (!nodePool_.empty())
	{
		nodePool_.clear();
	}
	start_ = start;
	goal_ = goal;

	auto& startNode = GetNode(start_);
	startNode.estCost = (goal_.x - start_.x) + (goal_.y - start_.y);
	startNode.parent = nullptr;
	// 周りを開く
	OpenAround(startNode);

	auto sort = [](const Node& a, const Node& b)->bool
	{
		auto aCost = a.cost + a.estCost;
		auto bCost = b.cost + b.estCost;
		if (aCost < bCost)
		{
			return true;
		}
		if (aCost == bCost)
		{
			return a.cost < b.cost;
		}
		return false;
	};

	int cnt = 0;
	while (openList_.size() > 0)
	{
		cnt++;
		// 基底回数を超えたら計算しない(これは途中までの通路を返す予定)
		if (cnt >= 100)
		{
			OutputDebugString(L"遠すぎて探索途中で打ち切りました");
			RecursiveCreateRoot(openList_.front());
			break;
		}
		auto node = openList_.front();
		OpenAround(node);
		openList_.erase(openList_.begin());
		std::sort(openList_.begin(), openList_.end(), sort);
		if (openList_.size() <= 0)
		{
			OutputDebugString(L"探索出来ませんルートが埋まっています");
			break;
		}
		if (openList_.front().pos == goal_)
		{
			RecursiveCreateRoot(openList_.front());
			break;
		}
	}
	std::reverse(root_.begin(), root_.end());
	return root_;
}

void Astar::Draw()
{
	//std::array<int, 5>color
	//{
	//	0x007fff,			// 防衛拠点				青
	//	0xff0f0f,			// 敵出現位置			赤
	//	0xafff00,			// 敵侵攻ルート			緑
	//	0xe3e3e3,			// 自機配置可能箇所		白
	//	0x000000			// 自機配置不可能箇所	黒（背景色）
	//};
	//for (int y = 0; y < MAP_SIZE; y++)
	//{
	//	int ychip = y * CHIP_SIZE;
	//	for (int x = 0; x < MAP_SIZE; x++)
	//	{
	//		int xchip = x * CHIP_SIZE;		
	//		if (mapData_[y][x] != MapState::WALL)
	//		{
	//			DrawBox(xchip, ychip, xchip + CHIP_SIZE, ychip + CHIP_SIZE, color[static_cast<int>(mapData_[y][x])], true);
	//		}
	//	}
	//}
	//for (int x = 0; x <= MAP_SIZE; x++)
	//{
	//	DrawLine(x * CHIP_SIZE, 0, x * CHIP_SIZE, CHIP_SIZE * MAP_SIZE, 0xffffff);
	//}
	//for (int y = 0; y <= MAP_SIZE; y++)
	//{
	//	DrawLine(0, y * CHIP_SIZE, MAP_SIZE * CHIP_SIZE, y * CHIP_SIZE, 0xffffff);
	//}
}

void Astar::OpenAround(const Node& node)
{
	VECTOR2 openTable[] =
	{
		{node.pos.x + 1, node.pos.y},
		{node.pos.x - 1, node.pos.y},
		{node.pos.x, node.pos.y + 1},
		{node.pos.x, node.pos.y - 1}
	};
	for (auto& open : openTable)
	{
		OpenNode(open, node);
	}
	// 開いたので閉じる
	CloseNode(node.pos);
}

void Astar::OpenNode(VECTOR2 pos, const Node& node)
{
	auto cost = node.cost;
	// コスト増加(今は1しか増加量が無いので+1)
	cost++;
	// 範囲外チェック
	if (!IsOutOfRange(pos))
	{
		return;
	}
	// 通れるかどうか
	auto chip = cusMap_.GetMapChipByIndex(pos);
	if (chip != MapChipName::ROOT && chip != MapChipName::SPAWNER && chip != MapChipName::MAINSTAY)
	{
		return;
	}
	auto& tmp = GetNode(pos);
	// tmpのstateがなにもされていないか
	if (tmp.state != NodeState::None)
	{
		return;
	}
	tmp.state = NodeState::Open;
	tmp.cost = cost;
	tmp.parent = &nodePool_[GetIdx(node.pos)];
	openList_.push_back(tmp);

	return;
}

bool Astar::IsOutOfRange(const VECTOR2& pos)
{
	if (pos.x >= 0 && pos.y >= 0 && pos.x < 10 && pos.y < 10)
	{
		return true;
	}
	return false;
}

Astar::Node& Astar::GetNode(VECTOR2 pos)
{
	int idx = GetIdx(pos);
	if (nodePool_.find(idx) != nodePool_.end())
	{
		nodePool_[idx].estCost = abs(goal_.x - pos.x) + abs(goal_.y - pos.y);
		return nodePool_[idx];
	}
	auto node = new Node(pos);
	node->estCost = abs(goal_.x - pos.x) + abs(goal_.y - pos.y);
	nodePool_.emplace(idx, *node);
	return nodePool_[idx];
}

void Astar::CloseNode(VECTOR2 pos)
{
	nodePool_[GetIdx(pos)].state = NodeState::Closed;
}

void Astar::RecursiveCreateRoot(Node& node)
{	
	/*auto chip = cusMap_.GetMapChipByIndex(node.pos);
	if (chip != MapChipName::MAINSTAY && chip != MapChipName::SPAWNER)
	{
		cusMap_.SetChipByIdx(node.pos, MapChipName::ROOT);
	}*/
	if (node.parent != nullptr)
	{
		RootDir root;
		if (node.pos.x == node.parent->pos.x)
		{
			root = node.pos.y > node.parent->pos.y ? RootDir::DOWN : RootDir::UP;
		}
		else
		{
			root = node.pos.x > node.parent->pos.x ? RootDir::RIGHT : RootDir::LEFT;
		}

		root_.emplace_back(root);
		RecursiveCreateRoot(*node.parent);
	}
}

int Astar::GetIdx(const VECTOR2 pos)
{
	return pos.x + (pos.y * cusMap_.GetMapSize().x);
}

