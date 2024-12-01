#include "pch.h"
#include "InGameScene.h"
#include "Player.h"
#include "CCTV.h"
#include "Camera.h"
#include "BarUI.h"
#include "WindowUI.h"
#include "Window.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::init()
{
	{
		Vector2 position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		Player* player = new Player(position, { 400,300 });
		CCTV* cctv = new CCTV(position + Vector2(400, 0), { 600,500 });
		player->setCCTV(cctv);
		addObject(player, LAYER::PLAYER);
		addObject(cctv, LAYER::UI);
		BarUI* bar = new BarUI({ position.x, position.y + 100 }, { 400, 50 });
		addObject(bar, LAYER::UI);
	}
	{
		WindowUI* windowBar = new WindowUI({ 500,100 }, { 400,50 }, WINDOW_TYPE::NEW, L"Bar.exe");
		Vector2 size = windowBar->getSize();
		BarUI* bar = new BarUI({ size.x / 2, size.y / 2 }, { 400,50 });
		windowBar->setUI(bar);
		addObject(windowBar, LAYER::UI);
	}
}