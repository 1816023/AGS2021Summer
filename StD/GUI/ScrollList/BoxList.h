#pragma once
#include "ScrollList.h"
struct BoxState
{
	VECTOR2 size;
	int color;
};

class BoxList : public ScrollList
{
public:
	BoxList(VECTOR2 pos, VECTOR2 size);
	~BoxList()override;
	// ���X�g�̍Ō�ɗv�f��ǉ�����
	bool Add(BoxState state);
	// ���X�g�̍Ō�̗v�f���폜����
	bool Del();

	void Update()override;
	void Draw()override;

private:
	std::list<BoxState>list_;
	int color_;
};

