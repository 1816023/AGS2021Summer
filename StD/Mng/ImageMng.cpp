#include "DxLib.h"
#include "ImageMng.h"

const int& ImageMng::GetID(std::wstring f_name)
{
	if (imgMap.find(f_name) == imgMap.end())
	{
		imgMap[f_name].resize(1);
		imgMap[f_name][0] = LoadGraph(f_name.c_str());
		int a = LoadGraph(f_name.c_str());
		if (imgMap[f_name][0] == -1)
		{
			AST();
		}
		
	}
	return imgMap[f_name][0];
}

const VEC_INT& ImageMng::GetID(std::wstring f_name, VECTOR2 divSize, VECTOR2 divCnt)
{
	if (imgMap.find(f_name) == imgMap.end())
	{
		imgMap[f_name].resize(divCnt.x * divCnt.y);
		LoadDivGraph(f_name.c_str(), divCnt.x * divCnt.y, divCnt.x, divCnt.y, divSize.x, divSize.y, &imgMap[f_name][0], false);
		if (imgMap[f_name][0] == -1)
		{
			AST();
		}
	}
	return imgMap[f_name];
}

ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
}