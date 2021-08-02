#pragma once
#include "../UI.h"
class BarGauge :
	public UI
{
public:
	BarGauge();
	~BarGauge()override;
	bool Update()override;
	void Draw()override;
private:
};

