#include "pch.h"
#include "TitleScene.h"
#include "ResourceManager.h"
#include"EventManager.h"
#include "ImageUI.h"
#include "TextUI.h"
#include "WindowUI.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "SceneManager.h"
#include "NewWindow.h"

TitleScene::TitleScene()
{
	_textUI = nullptr;
	_explanationUI = nullptr;
	_startBtn = nullptr;
	_tutorialBtn = nullptr;
	_exitBtn = nullptr;
}

TitleScene::~TitleScene()
{
}

void TitleScene::init()
{
#pragma region 
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
#pragma endregion

	_textUI = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 250 }, { 800, 300 }, WINDOW_TYPE::NEW, L"TitleText.exe");
	{
		TextUI* text = new TextUI();
		Vector2 size = _textUI->getSize();
		text->setupFont(100);
		text->setPosition({ size.x / 2, size.y / 3 });
		text->setText(L"ProjectEW");
		_textUI->setUI(text);
	}

	_explanationUI = new WindowUI({ SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2 + 100 }, { 400, 100 }, WINDOW_TYPE::NEW, L"ExplanationText.exe");
	{
		TextUI* text = new TextUI();
		Vector2 size = _explanationUI->getSize();
		text->setupFont(40);
		text->setPosition({ size.x / 2, size.y / 3 });
		text->setText(L"창을 닫아서 선택");
		_explanationUI->setUI(text);
	}

	_startBtn = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50 }, { 500, 100 }, WINDOW_TYPE::NEW, L"Start.exe");
	{
		TextUI* text = new TextUI();
		Vector2 size = _startBtn->getSize();
		text->setupFont(30);
		text->setPosition({ size.x / 2, size.y / 3 });
		text->setText(L"시작");
		_startBtn->setUI(text);
	}
	_startBtn->getWindow()->OnTryWindowCloseEvent += [this]()
		{
			GET_SINGLETON(EventManager)->changeScene(L"InGameScene");
		};

	_tutorialBtn = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200 }, { 500, 100 }, WINDOW_TYPE::NEW, L"Tutorial.exe");
	{
		TextUI* text = new TextUI();
		Vector2 size = _tutorialBtn->getSize();
		text->setupFont(30);
		text->setPosition({ size.x / 2, size.y / 3 });
		text->setText(L"튜토리얼");
		_tutorialBtn->setUI(text);
	}
	_tutorialBtn->getWindow()->OnTryWindowCloseEvent += [this]()
		{
			GET_SINGLETON(EventManager)->changeScene(L"TutorialScene");
		};

	_exitBtn = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 350 }, { 500, 100 }, WINDOW_TYPE::NEW, L"Exit.exe");
	{
		TextUI* text = new TextUI();
		Vector2 size = _exitBtn->getSize();
		text->setupFont(30);
		text->setPosition({ size.x / 2, size.y / 3});
		text->setText(L"나가기");
		_exitBtn->setUI(text);
	}
	_exitBtn->getWindow()->OnTryWindowCloseEvent += [this]()
		{
			
		};

	_textUI->getWindow()->setMoveable(false);
	_textUI->getWindow()->setCloseable(false);
	_explanationUI->getWindow()->setMoveable(true);
	_explanationUI->getWindow()->setCloseable(false);
	_startBtn->getWindow()->setMoveable(true);
	_startBtn->getWindow()->setCloseable(false);
	_tutorialBtn->getWindow()->setMoveable(true);
	_tutorialBtn->getWindow()->setCloseable(false);
	_exitBtn->getWindow()->setMoveable(true);
	_exitBtn->getWindow()->setCloseable(false);

	addObject(_textUI, LAYER::UI);
	addObject(_explanationUI, LAYER::UI);
	addObject(_startBtn, LAYER::UI);
	addObject(_tutorialBtn, LAYER::UI);
	addObject(_exitBtn, LAYER::UI);
}