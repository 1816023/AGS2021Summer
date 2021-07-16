#pragma once
#include "SpinBox.h"
class SpinBoxForFloat :
	public SpinBox
{
public:
	SpinBoxForFloat(VECTOR2 pos, int xSize,int NumOfDigits,int NumOfDigitsOfDecmal, int fontHandle = -1);
	~SpinBoxForFloat()override;
	void Draw()override;
	// �I�𒆂̃f�[�^���擾����
	const float GetSelData()const;
	// �f�[�^��}������
	void AddData(float data);
	void DeleteData();
	bool DeleteData(float data);
private:
	std::vector<float>vec_;
	// �\������
	int NumOfDigits_;
	// �����_�ȉ��̌���
	int NumOfDigitsOfDecmal_;
};

