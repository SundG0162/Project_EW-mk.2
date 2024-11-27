#include "pch.h"
#include "InGameScene.h"
#include "Player.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::init()
{
	{
		Player* player = new Player({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { 400,300 });
		cout << SCREEN_WIDTH / 2 << ", " << SCREEN_HEIGHT / 2;
	}
}