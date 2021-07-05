#pragma once
#include "ScrollList.h"
struct StringState
{
	std::string str;
	int color;
};

class StringList :
	public ScrollList
{
public:
	StringList(VECTOR2 pos, VECTOR2 size, int fonthande = -1);
	~StringList()override;
	// ���X�g�̍Ō�ɗv�f��ǉ�����
	bool Add(StringState state);
	// ���X�g�̍Ō�̗v�f���폜����
	bool Del();

	void Update()override;
	void Draw()override;
private:
	// string�^�d�l�p�̃t�H���g�n���h��
	int fontH_;

	std::list<StringState>list_;
};

