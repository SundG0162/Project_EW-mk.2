#include "pch.h"
#include "EnemyTestScene.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "ImageUI.h"
#include "TextUI.h"
#include "SpriteRenderer.h"
#include "BasicEnemy.h"
#include "Player.h"
#include "CCTV.h"
#include "BarUI.h"
#include "Utils.h"
#include "Core.h"
#include "SceneManager.h"
#include "SpawnManager.h"

void EnemyTestScene::init()
{
	{
		//LongHead* enemy = new LongHead();
		//enemy->setPos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
		//addObject(enemy, LAYER::ENEMY);
	}

	//{
	//	//85, 25�ȼ�
	//	//Ŀ���� �߾� �������� Ŀ��
	//	// �ϴ��� ���������� �ڵ�ȭ ���ϰ� ������ ������ ó����
	//	//GET_SINGLETON(ResourceManager)->textureLoad(L"Slider-Back", L"Texture\\SliderBack.bmp");
	//	GET_SINGLETON(ResourceManager)->loadTexture(L"Slider-Red", L"Texture\\SliderRed.bmp");
	//	Sprite* sprite = utils::SpriteParser::textureToSprite(
	//		GET_SINGLETON(ResourceManager)->findTexture(L"Slider-Red"));
	//	ImageUI* ui = new ImageUI({ 150,100 }, { 150, 125 }, WINDOW_TYPE::NEW, sprite, L"TestBarUI");
	//	ui->openTween();
	//	Vector2 scale = { 2,2 };
	//	ui->getComponent<SpriteRenderer>()->setScale({ 2,2 });
	//	ui->getComponent<SpriteRenderer>()->setOffset({ 0, -25 });
	//	addObject(ui, LAYER::UI);
	//}

	Object* target;
	{
		Vector2 position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		Player* player = new Player(position, { 400,300 });
		CCTV* cctv = new CCTV(position + Vector2(400, 0), { 600,500 });
		player->setCCTV(cctv);
		addObject(player, LAYER::PLAYER);
		addObject(cctv, LAYER::UI);

		target = player;
	}

	{
		BasicEnemy* basicEnemy = new BasicEnemy(target);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 1.f });
	}
	{
		BasicEnemy* basicEnemy = new BasicEnemy(target);
		GET_SINGLETON(SpawnManager)->addSpawnObject({ basicEnemy, 1.5f });
	}
}

void EnemyTestScene::render(HDC hDC)
{
	Vector2 middle = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	Vector2 size = { SCREEN_WIDTH, SCREEN_HEIGHT };
	//ELLIPSE_render(GET_SINGLETON(Core)->getBackDC(), middle.x, middle.y, size.x, size.y);
	//utils::Drawer::renderCircleColor(hDC, middle, 500, RGB(255, 0, 0), RGB(255, 0, 0));
	Scene::render(hDC);
}
