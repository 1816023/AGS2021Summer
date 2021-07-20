#pragma once
#include <vector>
#include <memory>
#include "../../VECTOR2.h"
#include "../Button/RectButton.h"
class PullDown
{
public:
	// pos:�`��ʒu
	// xSize:�`�悷�鉡��
	PullDown(VECTOR2 pos,int xSize,int fontHandle=0);
	~PullDown();
	// �ǉ����镶��
	bool Add(std::string str);

	void Update();
	void Draw();
	std::string GetSelStr();
private:
	// �`��p�X�N���[��
	int screen_;
	// 
	VECTOR2 size_;
	VECTOR2 pos_;
	int selKey_;
	std::vector<std::unique_ptr<RectButton>>list_;
	bool openFlag_;
	int fontHandle_;
};

