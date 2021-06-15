#pragma once
#include "../Scene/CustomMapScene.h"
class CustomMapScene;
struct CustomStateBase {
	CustomStateBase() {};
	virtual ~CustomStateBase()=default;

	virtual bool Init(CustomMapScene* scene) = 0;
	virtual void Update(CustomMapScene* scene) = 0;
	virtual void Draw(CustomMapScene* scene) = 0;
	virtual void Delete() = 0;
};