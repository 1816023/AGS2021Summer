#pragma once
#include "../UI.h"
class BarGauge :
	public UI
{
public:
	BarGauge(VECTOR2 pos,VECTOR2 size,int maxGauge );
	~BarGauge()override;
	bool Update()override;
	void Draw()override;

	// �l�̑���
	int Add(int num);
	// �l�̌���
	int Sub(int num);
	// �l�𕶎��Ƃ��ĕ\��
	void SetViewNumber(VECTOR2 pos);
	// �F�̐ݒ�
	// �����F�̓Q�[�W�����ŉ�����
	void SetColor(int gaugeColor = 0, int frameColor = 0xffffff);
	// �w�i�𖄂߂�
	void SetBackColor(bool isView, int color);
	// �Q�[�W�̍ő�l��ύX����
	void ChangeMaxGauge(int num);
private:
	int gauge_;
	bool isView_;
	bool isBackColor;
	int gaugeColor_;
	int frameColor_;
	int backColor_;
	int maxGauge_;
	VECTOR2 strPos_;
};

