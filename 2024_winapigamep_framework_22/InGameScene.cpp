#include "pch.h"
#include "InGameScene.h"
#include "Player.h"
#include "CCTV.h"
#include "Camera.h"
#include "BarUI.h"
#include "WindowUI.h"
#include "Window.h"
#include "LongHead.h"
#include "SpawnManager.h"

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
	CCTV* cctv = new CCTV(position + Vector2(400, 0), { 600,500 });
	player->setCCTV(cctv);
	addObject(player, LAYER::PLAYER);
	addObject(cctv, LAYER::UI);
	{
		LongHead* longhead = new LongHead();
		longhead->setPosition({ 0,0 });
		longhead->SetTarget(player);
		addObject(longhead, LAYER::ENEMY);
	}
	{
		LongHead* longhead = new LongHead({ 0,0 }, player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ longhead, 1.f });
	}
	{
		LongHead* longhead = new LongHead({ 0,0 }, player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ longhead, 1.5f });
	}
}