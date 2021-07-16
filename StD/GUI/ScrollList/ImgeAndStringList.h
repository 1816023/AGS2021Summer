#pragma once
#include "ScrollList.h"
struct IandSState
{
	int handle;
	VECTOR2 size;
	std::string str;
};
class ImgeAndStringList :
	public ScrollList
{
public:
	ImgeAndStringList(VECTOR2 pos, VECTOR2 size);
	~ImgeAndStringList()override;
	// ���X�g�̍Ō�ɗv�f��ǉ�����
	bool Add(int handle,std::string str);
	// ���X�g�̍Ō�̗v�f���폜����
	bool Del();

	void Update()override;
	void Draw()override;

private:
	std::list<IandSState>list_;

};

