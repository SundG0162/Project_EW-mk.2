#pragma once
#include "Scene.h"
class WindowUI;
class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();
public:
	void init() override;
private:
	WindowUI* _textUI;
	WindowUI* _startBtn;
	WindowUI* _tutorialBtn;
	WindowUI* _exitBtn;
};

