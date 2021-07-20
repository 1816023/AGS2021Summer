#include "NumberUI.h"
#include "Mng/ImageMng.h"
#include <DxLib.h>

void NumberUI::Draw(VECTOR2 pos, VECTOR2 offset, int number)
{
	VEC_INT handle = IMAGE_ID(L"data/image/number.png", VECTOR2{ 15, 21 }, VECTOR2{ 11, 1 });
	int digit = log10(number) + 1;
	for (int i = 0; i < digit; i++)
	{
		DrawRotaGraph(pos.x + offset.x * i, pos.y + offset.y, 1.0, 0.0, handle[number % 10], true);
		number /= 10;
	}
}

void NumberUI::TimeDraw(VECTOR2 pos, VECTOR2 offset, int minite, int second)
{
	VEC_INT handle = IMAGE_ID(L"data/image/number.png", VECTOR2{ 15, 21 }, VECTOR2{ 11, 1 });
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph(pos.x + offset.x * abs(i - 2), pos.y + offset.y, 1.0, 0.0, handle[minite % 10], true);
		minite /= 10;
	}
	DrawRotaGraph(pos.x + offset.x * 3, pos.y + offset.y,1.0, 0.0, handle[10], true);
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph(pos.x + offset.x * (abs(i - 2) + 4), pos.y + offset.y, 1.0, 0.0, handle[second % 10], true);
		second /= 10;
	}

}
