#pragma once
#include "BaseScene.h"
#include "../Map/Custom.h"
#include <functional>
#include <map>

#define MAX_NAME_SIZE 20	// �t�@�C�����̍ő啶����
#define STRING_HIGHT 20		// �����̍���
#define LINE_SPACING 30		// �s��
#define MAX_MAP_DRAW VECTOR2(854/1.5,480)
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

	// SET_STATE�ɑΉ�����Update�֐�
	void SetStateUpdate();					
	// MAP_CUNSTOM�ɑΉ�����Update�֐�
	void Map_CuntomUpdate();			
	// END_CUSTOM�ɑΉ�����Update�֐�
	void EndCustomUpdate();				
	// SET_STATE�ɑΉ�����Draw�֐�
	void SetStateDraw();				
	// MAP_CUNSTOM�ɑΉ�����Draw�֐�
	void MapCuntomDraw();				
	// END_CUSTOM�ɑΉ�����Draw�֐�
	void EndCustomDraw();				
	// ���͂��ꂽ�t�@�C�����ɃG���[���Ȃ����`�F�b�N����,true�Ȃ�G���[
	bool FileNameErrorCheck(std::wstring fileName);
};

