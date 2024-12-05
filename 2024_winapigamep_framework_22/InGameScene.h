#pragma once
#include "Scene.h"
class PanelUI;
class WindowUI;
class InGameScene : public Scene
{
public:
	InGameScene();
	~InGameScene();
public:
	void init() override;
	void update() override;
private:
	WindowUI* _powerPanel;
};