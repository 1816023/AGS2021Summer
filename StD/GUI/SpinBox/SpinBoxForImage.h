#pragma once
#include "SpinBox.h"
class SpinBoxForImage :
	public SpinBox
{
public:
	SpinBoxForImage(VECTOR2 pos, VECTOR2 size, VECTOR2 cOffset);
	~SpinBoxForImage()override;
	void Draw()override;
	// �I�𒆂̃f�[�^���擾����
	// �摜�n���h����Ԃ�
	const int GetSelData()const;
	// �f�[�^��}������
	// �摜�p�X���w�肷��
	void AddData(std::string path);
	// �f�[�^��}������
	// �摜�n���h�����w�肷��
	void AddData(int handle);
	// �f�[�^���폜����
	void DeleteData();
	// �w�肵���f�[�^���폜����
	// �摜�p�X���w�肷��
	bool DeleteData(std::string data);
	// �w�肵���f�[�^���폜����
	// �摜�n���h�����w�肷��
	bool DeleteData(int data);
	void StartEnd(bool key)override;
private:
	std::vector<int>vec_;

};

