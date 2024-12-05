#pragma once
#include "Scene.h"
class InGameScene : public Scene
{
public:
	InGameScene();
	~InGameScene();
public:
	void init() override;
	void update() override;
};