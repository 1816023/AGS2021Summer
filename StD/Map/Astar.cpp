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
	// ������J��
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
		// ���񐔂𒴂�����v�Z���Ȃ�(����͓r���܂ł̒ʘH��Ԃ��\��)
		if (cnt >= 100)
		{
			OutputDebugString(L"�������ĒT���r���őł��؂�܂���");
			RecursiveCreateRoot(openList_.front());
			break;
		}
		auto node = openList_.front();
		OpenAround(node);
		openList_.erase(openList_.begin());
		std::sort(openList_.begin(), openList_.end(), sort);
		if (openList_.size() <= 0)
		{
			OutputDebugString(L"�T���o���܂��񃋁[�g�����܂��Ă��܂�");
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
	//	0x007fff,			// �h�q���_				��
	//	0xff0f0f,			// �G�o���ʒu			��
	//	0xafff00,			// �G�N�U���[�g			��
	//	0xe3e3e3,			// ���@�z�u�\�ӏ�		��
	//	0x000000			// ���@�z�u�s�\�ӏ�	���i�w�i�F�j
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
	// �J�����̂ŕ���
	CloseNode(node.pos);
}

void Astar::OpenNode(VECTOR2 pos, const Node& node)
{
	auto cost = node.cost;
	// �R�X�g����(����1���������ʂ������̂�+1)
	cost++;
	// �͈͊O�`�F�b�N
	if (!IsOutOfRange(pos))
	{
		return;
	}
	// �ʂ�邩�ǂ���
	auto chip = cusMap_.GetMapChipByIndex(pos);
	if (chip != MapChipName::ROOT && chip != MapChipName::SPAWNER && chip != MapChipName::MAINSTAY)
	{
		return;
	}
	auto& tmp = GetNode(pos);
	// tmp��state���Ȃɂ�����Ă��Ȃ���
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

