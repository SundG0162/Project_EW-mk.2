#include "pch.h"
#include "TitleScene.h"
#include "TextUI.h"
#include "ImageUI.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "InputManager.h"
#include "PopupManager.h"

void TitleScene::init()
{
	/*{
		Sprite* sprite = utils::SpriteParser::textureToSprite(
			GET_SINGLETON(ResourceManager)->findTexture(L"Title-1"));
		ImageUI* ui = new ImageUI({ 100,500 }, { 150, 850 }, WINDOW_TYPE::NEW, sprite);
		addObject(ui, LAYER::UI);
		ui->openTween(1.f);
		ui->getComponent<SpriteRenderer>()->setScale({ 9,9 });
	}
	{
		Sprite* sprite = utils::SpriteParser::textureToSprite(
			GET_SINGLETON(ResourceManager)->findTexture(L"Title-2"));
		ImageUI* ui = new ImageUI({ 270,550 }, { 200, 850 }, WINDOW_TYPE::NEW, sprite);
		addObject(ui, LAYER::UI);
		ui->openTween(1.2f);
		ui->getComponent<SpriteRenderer>()->setScale({ 10,10 });
	}
	{
		Sprite* sprite = utils::SpriteParser::textureToSprite(
			GET_SINGLETON(ResourceManager)->findTexture(L"Title-3"));
		ImageUI* ui = new ImageUI({ 450,450 }, { 220, 800 }, WINDOW_TYPE::NEW, sprite);
		addObject(ui, LAYER::UI);
		ui->openTween(1.4f);
		ui->getComponent<SpriteRenderer>()->setScale({ 14,14 });
	}
	{
		Sprite* sprite = utils::SpriteParser::textureToSprite(
			GET_SINGLETON(ResourceManager)->findTexture(L"Title-4"));
		ImageUI* ui = new ImageUI({ 600,500 }, { 100, 600 }, WINDOW_TYPE::NEW, sprite);
		addObject(ui, LAYER::UI);
		ui->openTween(1.6f);
		ui->getComponent<SpriteRenderer>()->setScale({ 4,4 });
	}*/
	cout << "I'm on titleScene";
}