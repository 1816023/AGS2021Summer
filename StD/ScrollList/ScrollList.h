#pragma once
#include <list>
#include <array>
#include <string>
#include <memory>
#include "../VECTOR2.h"
enum class ListType
{
	STRING,
	IMAGE,
	COLOR_BOX,
	Max
};

class ScrollList
{
public:
	
	ScrollList(VECTOR2 pos,VECTOR2 size,ListType type);
	virtual ~ScrollList();
	virtual bool Del()=0;
	virtual void Update()=0;
	virtual void Draw()=0;
private:
protected:
	// �X�N���[����
	float scrollPos_;
	// �`��ʒu�i����j
	VECTOR2 pos_;
	// �`��T�C�Y
	VECTOR2 size_;
	// ���X�g�^�C�v
	ListType type_;
	// �`��X�N���[��
	int screen_;

};

