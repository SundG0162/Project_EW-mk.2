#include "pch.h"
#include "InGameScene.h"
#include "Player.h"
#include "CCTV.h"
#include "WindowUI.h"
#include "Window.h"
#include "SpawnManager.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "EventManager.h"
#include "TextUI.h"
#include "UpgradeUI.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::init()
{
	Vector2 position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	Player* player = new Player(position, { 400,300 });
	addObject(player, LAYER::PLAYER);
}

void InGameScene::update()
{
	Scene::update();
	if (GET_KEYDOWN(KEY_TYPE::K))
	{
		GET_SINGLETON(EventManager)->changeScene(L"TitleScene");
	}
}
