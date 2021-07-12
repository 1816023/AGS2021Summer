#pragma once
#include "SpinBox.h"
class SpinBoxForString :
	public SpinBox
{
public:
	SpinBoxForString(VECTOR2 pos, int xSize, int fontHandle = -1);
	~SpinBoxForString()override;
	bool Update()override;
	void Draw()override;
	// �I�𒆂̃f�[�^���擾����
	const std::string GetSelData()const;
	// �f�[�^��}������
	void AddData(std::string data);
	// �f�[�^���폜����
	bool DeleteData();
	// �w�肵���f�[�^���폜����
	bool DeleteData(std::string data);
private:
	std::vector<std::string>vec_;

};

