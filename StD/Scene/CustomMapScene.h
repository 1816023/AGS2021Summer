#pragma once
#include "BaseScene.h"
#include "../Map/Custom.h"
#include <functional>
#include <map>

enum class CustomState {
	SET_STATE,			// �}�b�v�̕��⍂����ݒ肷����
	MAP_CUSTOM,			// �}�b�v���쐬���Ă�����
	END_CUSTOM,			// �쐬�I����̕ۑ����̏��
	MAX
};
class CustomMapScene :
	public BaseScene
{
public:
	CustomMapScene();
	~CustomMapScene();

	unique_Base Update(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::MAIN; }
private:
	void Draw()override;
	std::unique_ptr<Custom>map_;
	std::map<CustomState, std::function<void(void)>>updateFunc_;
	std::map<CustomState, std::function<void(void)>>drawFunc_;
	CustomState nowState_;
	int mapSizeX;
	int mapSizeY;
	TCHAR fileName[20];

	void SetStateUpdate();				// SET_STATE�ɑΉ�����Update�֐�	
	void Map_CuntomUpdate();			// MAP_CUNSTOM�ɑΉ�����Update�֐�
	void EndCustomUpdate();				// END_CUSTOM�ɑΉ�����Update�֐�
	void SetStateDraw();				// SET_STATE�ɑΉ�����Draw�֐�	
	void MapCuntomDraw();				// MAP_CUNSTOM�ɑΉ�����Draw�֐�
	void EndCustomDraw();				// END_CUSTOM�ɑΉ�����Draw�֐�

};

