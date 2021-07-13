#pragma once
#include "BaseScene.h"
#include <list>

// ��Փx
enum class Difficulity
{
	Tutorial,
	Easy,
	Normal,
	Hard
};

class Button;
class Canvas;
class MainScene :
	public BaseScene
{
public:
	MainScene();
	~MainScene();

	unique_Base Update(unique_Base own) override;
	SCENE_ID GetScnID(void) override { return SCENE_ID::MAIN; }
private:
	// �X�V�֐��|�C���^
	using UpdateFunc_t = void(MainScene::*)();
	void GameModeSelectUpdate();
	void DifficuritySelectUpdate();
	UpdateFunc_t updater_;
	// �`��֐��|�C���^
	using DrawFunc_t = void(MainScene::*)();
	void GameModeSelectDraw();
	void DifficuritySelectDraw();

	DrawFunc_t drawer_;
	void Draw()override;
	void DrawUI()override;
	std::unique_ptr<Canvas> gameModeCanvas_;
	std::unique_ptr<Canvas> difSelectCanvas_;
	bool gameTransition_;
	bool customTransition_;
	bool mapSelectTransition_;
	Difficulity difficulity_;
};

