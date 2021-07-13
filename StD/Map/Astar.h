#pragma once
#include "../VECTOR2.h"
#include <vector>
#include <map>
#include "../Unit/Enemy/EnemyType.h"
enum class NodeState
{
	None,		// �{�����Ă��Ȃ�
	Open,		// ���{����
	Closed,		// �{���I��
};


class Custom;
class Astar
{
public:
	Astar(Custom& map);
	// A*�Ń��[�g�쐬
	std::vector<RootDir> AstarStart(VECTOR2 start, VECTOR2 goal);
	void Draw();
private:
	struct Node
	{
		Vec2Int pos;		// ���W
		NodeState state;	// �{�����
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
	// ����̃m�[�h���I�[�v������
	void OpenAround(const Node& node);
	// �m�[�h���I�[�v������
	void OpenNode(VECTOR2 pos, const Node& node);
	// �͈͊O�`�F�b�N
	bool IsOutOfRange(const VECTOR2& pos);
	// �v�[������m�[�h���擾(�Ȃ��ꍇ�͐V�K�쐬)
	Node& GetNode(VECTOR2 pos);
	// �m�[�h�����(�m�[�h�̃v�[������)
	void CloseNode(VECTOR2 pos);
	// �ċA�I�Ƀ��[�g���쐬����
	void RecursiveCreateRoot(Node& node);
	// ���W����C���f�b�N�X���擾
	int GetIdx(const VECTOR2 pos);

	VECTOR2 start_;	// �X�^�[�g�́[�h
	VECTOR2 goal_;	// �S�[���m�[�h
	std::map<int,Node> nodePool_;	// �m�[�h���ꎞ�ۑ����Ă������
	std::vector<Node> openList_;	// �I�[�v�����Ă���m�[�h�̃��X�g
	std::vector<RootDir> root_;		// ���[�g
	Custom& cusMap_;
};

