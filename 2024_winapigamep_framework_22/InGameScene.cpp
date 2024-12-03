#include "pch.h"
#include "InGameScene.h"
#include "Player.h"
#include "CCTV.h"
#include "Camera.h"
#include "BarUI.h"
#include "WindowUI.h"
#include "Window.h"
#include "BasicEnemy.h"
#include "SpawnManager.h"
#include "Beacon.h"

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
	cctv->initialize(player);
	addObject(player, LAYER::PLAYER);
	addObject(cctv, LAYER::UI);

	/*Beacon* beacon = new Beacon({ position.x - 500, position.y }, { 300,300 });
	addObject(beacon, LAYER::UI);*/

	{
		BasicEnemy* basicEnemy = new BasicEnemy(player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 1.f });
	}
	{
		BasicEnemy* basicEnemy = new BasicEnemy(player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 1.5f });
	}
	{
		BasicEnemy* basicEnemy = new BasicEnemy(player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 2.f });
	}
	{
		BasicEnemy* basicEnemy = new BasicEnemy(player);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 2.5f });
	}
}