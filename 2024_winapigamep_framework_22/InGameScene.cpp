#include "pch.h"
#include "InGameScene.h"
#include "Player.h"
#include "CCTV.h"
#include "WindowUI.h"
#include "Window.h"
#include "SpawnManager.h"
#include "WindowManager.h"
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
	CCTV* cctv = new CCTV(position + Vector2(400, 0), { 600,500 });
	player->setCCTV(cctv);
	cctv->initialize(player);
	addObject(player, LAYER::PLAYER);
	addObject(cctv, LAYER::PLAYER);
	WindowUI* testUI = new WindowUI({ 300,300 }, { 320,480 }, WINDOW_TYPE::NEW, L"Upgrade.exe");
	UpgradeUI* upgrade = new UpgradeUI();
	testUI->setUI(upgrade);
	addObject(testUI, LAYER::UI);
}