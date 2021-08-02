#pragma once
#include "../Scene/CustomMapScene.h"
class CustomMapScene;
struct CustomStateBase {
	CustomStateBase() {};
	virtual ~CustomStateBase()=default;
	// ‰Šú‰»
	virtual bool Init(CustomMapScene* scene) = 0;
	// XV
	virtual void Update(CustomMapScene* scene) = 0;
	// 
	virtual void DrawUI(CustomMapScene* scene) = 0;
	virtual void Draw(CustomMapScene* scene) {};
	virtual void Delete() = 0;
};