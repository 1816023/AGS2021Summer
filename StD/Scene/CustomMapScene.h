#pragma once
#include "BaseScene.h"
#include "../Map/Custom.h"
#include <functional>
#include <memory>
#include <map>
#include <list>
#include "../Button/RoundRectButton.h"
#include "../CustomState/CustomState.h"
#define MAX_NAME_SIZE 20	// �t�@�C�����̍ő啶����
#define STRING_HIGHT 20		// �����̍���
#define LINE_SPACING 30		// �s��
#define SELECT_UI_POS std::pair<VECTOR2,VECTOR2>(VECTOR2(DEF_SCREEN_SIZE_X/1.5,0),VECTOR2(DEF_SCREEN_SIZE_X,DEF_SCREEN_SIZE_Y))
#define TEXT_UI_POS std::pair<VECTOR2,VECTOR2>(VECTOR2(0,DEF_SCREEN_SIZE_Y/1.25),VECTOR2(SELECT_UI_POS.first.x-10,DEF_SCREEN_SIZE_Y))
struct ButtomState {
	VECTOR2 luPos;		// ������W
	VECTOR2 rdPos;		// �E����W
	bool pushFlag;		// �����t���O
	std::wstring name;	// �{�^���̖��O
	int CorH;			// �{�^���̐F�܂��͉摜�n���h��
	std::function<void(ButtomState&)> func;	// �{�^���������ꂽ�Ƃ��ɌĂ΂��֐�
};

enum class CustomState {
	SELECT_FILE,		// �����̃t�@�C������I������
	SET_STATE,			// �}�b�v�̕��⍂����ݒ肷����
	MAP_CUSTOM,			// �}�b�v���쐬���Ă�����
	ENEMY_CUSTOM,		// �G�̔z�u�ƓG�̐N�U���[�g�ݒ�
	END_CUSTOM,			// �쐬�I����̕ۑ����̏��
	MAX
};
struct ButtonText
{
	std::string str_;		// ����
	unsigned int color_;	// �����F
	VECTOR2 pos_;			// �`��ʒu
};
class Astar;
class SelectFile;
class SetState;
class MapCustom;
class EnemyCustom;
class EndCustom;
class CustomMapScene :
	public BaseScene
{
public:
	CustomMapScene();
	~CustomMapScene();

	unique_Base Update(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::MAIN; }
private:
	// �������p
	bool Init();
	// ��{�I�ȃ��C�����̕`��
	void Draw()override;
	// UI�n�̕`��
	void DrawUI()override;
	// custom�N���X�̃|�C���^�[
	std::unique_ptr<Custom>cusMap_;
	
	//
	std::map<CustomState, std::unique_ptr<CustomStateBase>>custom_;
	// ���݂̃X�e�[�^�X
	CustomState nowState_;
	// �}�b�v�t�@�C�����̕ۑ��p
	TCHAR fileName_[20];
	// �ϓ�����A���t�@�l
	int blendAlpha_;
	// �t�@�C�����烍�[�h����������
	std::map<MapChipName,std::string> textData_;
	// �ۑ�����Ƃ��ɍŒ���̏�ԂɂȂ��Ă��邩��
	// return 0 �G���[�Ȃ�
	// return 1 �����_�G���_�̐��ُ�
	// return 2 �����_�̐��ُ�
	// return 3 �G���_�̐��ُ�
	int SaveCheck();
	// ���͂��ꂽ�t�@�C�����ɃG���[���Ȃ����`�F�b�N����,true�Ȃ�G���[
	bool FileNameErrorCheck(std::wstring fileName);
	// ���������t�@�C�����烍�[�h����
	bool LoadText(std::string type);

	friend SelectFile;
	friend SetState;
	friend MapCustom;
	friend EnemyCustom;
	friend EndCustom;
};

