#pragma once
#include "ScrollList.h"
class ImageList :
	public ScrollList
{
public:
	ImageList(VECTOR2 pos, VECTOR2 size, ListType type);
	~ImageList()override;
	// ���X�g�̍Ō�ɗv�f��ǉ�����
	bool Add(int handle);
	// ���X�g�̍Ō�̗v�f���폜����
	bool Del();

	void Update()override;
	void Draw()override;

private:
	std::list<int>list_;

};

