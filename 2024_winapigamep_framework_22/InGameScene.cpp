#include "pch.h"
#include "InGameScene.h"
#include "Player.h"
#include "CCTV.h"
#include "Camera.h"
#include "BarUI.h"
#include "WindowUI.h"
#include "Window.h"
#include "FadeInOut.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::init()
{
		Vector2 position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	{
		Player* player = new Player(position, { 400,300 });
		CCTV* cctv = new CCTV(position + Vector2(400, 0), { 600,500 });
		player->setCCTV(cctv);
		addObject(player, LAYER::PLAYER);
		addObject(cctv, LAYER::UI);
	}
	{
		FadeInOut* fade = new FadeInOut(position, { 400,300 });
		fade->init(3.f, FADE_TYPE::FADE_OUT);
		addObject(fade, LAYER::UI);
	}
}