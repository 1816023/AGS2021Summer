#pragma once
#include "../VECTOR2.h"
#include <string>
#include <vector>
enum class Justified
{

};
class Button;

class Canvas
{
public:
	Canvas(VECTOR2 pos, VECTOR2 size);
	~Canvas();
	void AddButton(Button button, int id = -1);
	void AddButton(Button button, std::string name = "");
private:
	VECTOR2 pos_;
	VECTOR2 size_;
};

